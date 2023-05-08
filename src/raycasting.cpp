#include <cmath>  
#include <limits>
#include <iostream>
#include <math.h>

#include "PPMGenerator.h"
#include "vectors.h"
#include "graphicsTools.h"

#define D 5
#define DELTA 0.00000001; //nudge to direction vector if equal to up vector
#define PI 3.14159265
#define EPSILON 0.01

// returns degrees converted to radians
float toRadians(float degrees) {
	return degrees * PI / 180.0; 
}

// returns view window width from hfov
float getViewWindowWidth(float hfov) {
	float angle = toRadians(hfov) * 0.5f;
	return 2 * D * std::tan(angle);
}

// returns view window width based on aspectRatio 
float getViewWindowWidth(float viewWindowHeight, float aspectRatio) {
	return viewWindowHeight * aspectRatio;
}

// returns view window height based on vfov
float getViewWindowHeight(float vfov) {
	float angle = toRadians(vfov) * 0.5f;
	return 2 * D * std::tan(angle);
}

// returns view window height based on aspectRatio
float getViewWindowHeight(float viewWindowWidth, float aspectRatio) {
	return viewWindowWidth / aspectRatio;
}

// generates rays based on scene specifications
void makeRays(ray_t** rays, sceneSpecs_t& specs, float viewWindowWidth, float viewWindowHeight) {
	vector3_t uVector, vVector, ulVector, urVector, llVector, lrVector, tempVector;

	uVector = normalize(crossProduct(specs.viewDirectionVector, specs.upVector));
	vVector = normalize(crossProduct(uVector, specs.viewDirectionVector));  
	
	vector3_t viewWindowVector = addVectors(specs.viewOriginVector, multiplyCoefficient(specs.viewDirectionVector, D));
	vector3_t uPrimeVector = multiplyCoefficient(uVector, viewWindowWidth / 2);
	vector3_t vPrimeVector = multiplyCoefficient(vVector, viewWindowHeight / 2);

	ulVector = addVectors(viewWindowVector, addVectors(multiplyCoefficient(uPrimeVector, -1), vPrimeVector));
	urVector = addVectors(viewWindowVector, addVectors(uPrimeVector, vPrimeVector)); 
	llVector = addVectors(viewWindowVector, addVectors(multiplyCoefficient(uPrimeVector, -1), multiplyCoefficient(vPrimeVector, -1)));
	lrVector = addVectors(viewWindowVector, addVectors(uPrimeVector, multiplyCoefficient(vPrimeVector, -1)));
	
	vector3_t deltaH = multiplyCoefficient(subtractVectors(urVector, ulVector), 1.0 / (specs.imageWidth - 1));
	vector3_t deltaV = multiplyCoefficient(subtractVectors(llVector, ulVector), 1.0 / (specs.imageHeight - 1));

	// generate ray position and direction
	vector3_t fullDeltaH, fullDeltaV, viewWindowPixelVector;
	for(int i = 0; i < specs.imageHeight; i++) {
		fullDeltaV = multiplyCoefficient(deltaV, i);

		for(int j = 0; j < specs.imageWidth; j++) {
			fullDeltaH = multiplyCoefficient(deltaH, j);
			viewWindowPixelVector = addVectors(ulVector, addVectors(fullDeltaV, fullDeltaH));
			//viewWindowPixelVector = addVectors(ulVector, addVectors(deltaCenter, addVectors(fullDeltaV, fullDeltaH)));

			rays[i][j].position = specs.isParallel ? subtractVectors(viewWindowPixelVector, viewWindowVector) : specs.viewOriginVector; 
			rays[i][j].direction = normalize(subtractVectors(viewWindowPixelVector, rays[i][j].position)); 
		}
	}
}

// returns distance of sphere that is intersected by ray, -1 if no intersection
float intersectsSphere(ray_t& ray, sphere_t& sphere) {
	ray.direction = normalize(ray.direction);
	vector3_t diffVector = subtractVectors(ray.position, sphere.position);

	float A = dotProduct(ray.direction, ray.direction);
	float B = 2 * dotProduct(ray.direction, diffVector);
    float C = dotProduct(diffVector, diffVector) - (sphere.radius * sphere.radius);
	
    float discriminate = (B * B) - (4 * A * C);

    if(discriminate <= 0) {
        return std::numeric_limits<double>::infinity();
    }

    float discriminateSqrt = sqrt(discriminate);

	if(std::min((-B + discriminateSqrt) / (2 * A), (-B - discriminateSqrt) / (2 * A)) < 0) {
		return -1;
	}

    return std::min((-B + discriminateSqrt) / (2 * A), (-B - discriminateSqrt) / (2 * A));
}

// returns texture color from uv texture coordinates
color_t getTextureColor(float u, float v, texture_t* texture) {
	int textureHeightCoordinate = round(v * (texture->height - 1));
	int textureWidthCoordinate = round(u * (texture->width - 1));
	
	return texture->textureColors[textureHeightCoordinate][textureWidthCoordinate];
}

// returns barycentric coordinates in form beta, lambda, alpha of triangle 
vector3_t getBarycentricCoordinates(vector3_t& intersectionPoint, triangle_t& triangle, std::vector<vector3_t*>& vertices) {
	float determinate = ((dotProduct(triangle.e1, triangle.e1) * dotProduct(triangle.e2, triangle.e2)) - (dotProduct(triangle.e1, triangle.e2) * dotProduct(triangle.e1, triangle.e2)));
	vector3_t coordinates;

	if(determinate == 0) {
		coordinates.x = 0;
		coordinates.y = 0;
		coordinates.z = 0;
		return coordinates;
	}
	
	vector3_t ep = subtractVectors(intersectionPoint, *vertices.at(triangle.pointIndices[0]));
	
	coordinates.x = (dotProduct(triangle.e2, triangle.e2) * dotProduct(triangle.e1, ep) - dotProduct(triangle.e1, triangle.e2) * dotProduct(triangle.e2, ep)) / determinate;
	coordinates.y = (dotProduct(triangle.e1, triangle.e1) * dotProduct(triangle.e2, ep) - dotProduct(triangle.e1, triangle.e2) * dotProduct(triangle.e1, ep)) / determinate;
	coordinates.z = 1 - coordinates.x - coordinates.y;
	
	return coordinates;
}

// returns distance of triangle that is intersected by ray, -1 if no intersection
// also calculates normal surface normal for ray
float intersectsTriangle(ray_t& ray, triangle_t& triangle, std::vector<vector3_t*>& vertices, std::vector<vector3_t*>& normals, vector3_t* surfaceNormal) {
	float d = -sumVector(multiplyVectors(triangle.normal, *vertices.at(triangle.pointIndices[0])));
	float denominator = sumVector(multiplyVectors(triangle.normal, ray.direction));

	if(denominator == 0) {
		return -1;
	}

	float distance = -(sumVector(multiplyVectors(triangle.normal, ray.position)) + d) / denominator; 
	if(distance < 0) {
		return -1;
	}

	vector3_t planeIntersectionPoint = addVectors(ray.position, multiplyCoefficient(ray.direction, distance));
	vector3_t coordinates = getBarycentricCoordinates(planeIntersectionPoint, triangle, vertices);

	if(!((coordinates.x > 0 && coordinates.x < 1) && (coordinates.y > 0 && coordinates.y < 1) && (coordinates.z > 0 && coordinates.z < 1))) {
		return -1;
	}

	
	if(surfaceNormal != NULL) {
		if((triangle.normalIndices[0] != -1 && triangle.normalIndices[2] != -1 && triangle.normalIndices[2] != -1)) {
			*surfaceNormal = normalize(addVectors(multiplyCoefficient(normalize(*normals[triangle.normalIndices[0]]), coordinates.z), addVectors(multiplyCoefficient(normalize(*normals[triangle.normalIndices[1]]), coordinates.x), multiplyCoefficient(normalize(*normals[triangle.normalIndices[2]]), coordinates.y))));
		} else {
			*surfaceNormal = triangle.normal;
		}
	}

    return distance;
}

// returns shadow flag for a given ray
float getShadowFlag(ray_t shadowOriginRay, std::vector<sphere_t*> spheres, std::vector<triangle_t*> triangles, std::vector<vector3_t*> vertices, std::vector<vector3_t*> normals, float distanceToLight, bool isPointLight) {
	sphere_t clostestSphere;
	float distance, closestSphereDistance = std::numeric_limits<float>::max();
    for(int i = 0; i < spheres.size(); i++) {
		distance = intersectsSphere(shadowOriginRay, *(spheres.at(i)));
        
		if(distance >= 0 && distance < closestSphereDistance) {
			clostestSphere = *(spheres.at(i));
			closestSphereDistance = distance;
		}
    }

	triangle_t closestTriangle;
	float closestTriangleDistance = std::numeric_limits<float>::max();
	for(int i = 0; i < triangles.size(); i++) {
		distance = intersectsTriangle(shadowOriginRay, *(triangles.at(i)), vertices, normals, NULL);
        
		if(distance >= 0 && distance < closestTriangleDistance) {
			closestTriangle = *(triangles.at(i));
			closestTriangleDistance = distance;
		}
    }

	if((closestSphereDistance == std::numeric_limits<float>::max() || closestSphereDistance == std::numeric_limits<double>::infinity()) &&
	   (closestTriangleDistance == std::numeric_limits<float>::max() || closestTriangleDistance == std::numeric_limits<double>::infinity())) {
		return 1.0;
	}

	float closestDistance = closestSphereDistance < closestTriangleDistance ? closestSphereDistance : closestTriangleDistance;

	if(isPointLight) {
		return closestDistance < distanceToLight && closestDistance > EPSILON ? 0.0 : 1.0;
	} 
	
	return closestDistance > EPSILON ? 0.0 : 1.0;
}

// returns a shadow flag sampled from an area for a shadow flag that simulates soft shadows
float getSampledShadowFlag(ray_t shadowOriginRay, std::vector<sphere_t*> spheres, std::vector<triangle_t*> triangle, std::vector<vector3_t*> vertices, std::vector<vector3_t*> normals, vector3_t surfaceIntersectionVector, vector3_t lightVector, bool isPointLight, int samples) {
	ray_t shadowOriginRaySample;
	vector3_t lightVectorSample;
	float shadowFlagSum = 0;
	shadowOriginRaySample.position = shadowOriginRay.position;

	for(int i = 0; i < samples; i++) {
		lightVectorSample.x = lightVector.x + (-0.01 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.01 + 0.01))));
		lightVectorSample.y = lightVector.y + (-0.01 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.01 + 0.01))));
		lightVectorSample.z = lightVector.z + (-0.01 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.01 + 0.01))));
		shadowOriginRaySample.direction = isPointLight ? normalize(subtractVectors(lightVectorSample, surfaceIntersectionVector)) : normalize(negative(lightVectorSample));
		
		shadowFlagSum += getShadowFlag(shadowOriginRaySample, spheres, triangle, vertices, normals, vectorDistance(surfaceIntersectionVector, lightVectorSample), isPointLight);
	}

	return shadowFlagSum / (1.0 * samples);
}

// returns color of ray based on sphere intersection, illumination, and shadowing
color_t shade_ray(std::vector<light_t*> lights, std::vector<sphere_t*> spheres, sphere_t sphere, vector3_t viewDirectionVector, vector3_t surfaceIntersectionVector, float distanceFromCamera, sceneSpecs_t specs) {
	vector3_t ambientIlluminationColor, diffuseIlluminationColor, specularIlluminationColor, surfaceNormal, ligthDirectionVector, hVector;
	color_t diffuseColor;
	ray_t shadowOriginRay;
	float shadowFlag, attentuationFactor, distanceToLight;

	surfaceNormal = normalize(multiplyCoefficient(subtractVectors(surfaceIntersectionVector, sphere.position), 1.0 / sphere.radius));

	if(sphere.isTextured) {
		float phi = acos(surfaceNormal.z);
		float theta = atan2(surfaceNormal.y, surfaceNormal.x);
		float u = theta >= 0 ? theta / (2 * PI) : (theta + (2 * PI)) / (2 * PI);
		float v = phi / PI;
		
		diffuseColor = getTextureColor(u, v, sphere.texture);
	} else {
		diffuseColor = sphere.materialColor->diffuseColor;
	}

	// set initial illumination to ambient 
	vector3_t illuminationColor = multiplyCoefficient(colorToVector(diffuseColor), sphere.materialColor->ambient); 

	// loop over every light and add its illumination and calculate its shadow flag
	for(int i = 0; i < lights.size(); i++) {
		ligthDirectionVector = lights.at(i)->w == 1.0 ? normalize(subtractVectors(lights.at(i)->vector, surfaceIntersectionVector)) : normalize(negative(lights.at(i)->vector)); 
		hVector = normalize(averageVector(ligthDirectionVector, viewDirectionVector));
		
		shadowOriginRay.position = surfaceIntersectionVector;
		shadowOriginRay.direction = ligthDirectionVector;
		shadowFlag = getSampledShadowFlag(shadowOriginRay, spheres, specs.triangles, specs.vertices, specs.normals, surfaceIntersectionVector, lights.at(i)->vector, lights.at(i)->w, 100);

		distanceToLight = vectorDistance(lights.at(i)->vector, surfaceIntersectionVector);
		attentuationFactor = lights.at(i)->w == 1.0 ? 1.0 / (lights.at(i)->c1 + (lights.at(i)->c2 * distanceToLight) + (lights.at(i)->c3 * distanceToLight * distanceToLight)) : 1.0;
		
		diffuseIlluminationColor = multiplyCoefficient(multiplyCoefficient(colorToVector(diffuseColor), sphere.materialColor->diffuse), std::max(0.0f, dotProduct(surfaceNormal, ligthDirectionVector)));
		specularIlluminationColor = multiplyCoefficient(multiplyCoefficient(colorToVector(sphere.materialColor->specularColor), sphere.materialColor->specular), float(pow(std::max(0.0f, dotProduct(surfaceNormal, hVector)), sphere.materialColor->specularFalloff))); 
		illuminationColor = addVectors(illuminationColor, multiplyCoefficient(multiplyCoefficient(multiplyVectors(colorToVector(lights.at(i)->color), addVectors(diffuseIlluminationColor, specularIlluminationColor)), shadowFlag), attentuationFactor));
	}
	
	// determine depthcue alpha
	float alphaDepthcue;
	if(distanceFromCamera <= specs.dNear) {
		alphaDepthcue = specs.alphaMax;
	} else if(distanceFromCamera >= specs.dFar) {
		alphaDepthcue = specs.alphaMin;
	} else {
		alphaDepthcue = specs.alphaMin + (specs.alphaMax - specs.alphaMin) * ((specs.dFar - distanceFromCamera) / (specs.dFar - specs.dNear));
	}
	
	color_t finalColor =  vectorToColor(addVectors(multiplyCoefficient(clampVector(illuminationColor, 1, 1, 1), alphaDepthcue), multiplyCoefficient(colorToVector(specs.depthcueColor), 1.0 - alphaDepthcue)));;
	
	// return color with depthcue weight applied
	return vectorToColor(addVectors(multiplyCoefficient(clampVector(illuminationColor, 1, 1, 1), alphaDepthcue), multiplyCoefficient(colorToVector(specs.depthcueColor), 1.0 - alphaDepthcue)));
}

// returns color of ray based on triangle intersection, illumination, and shadowing
color_t shade_ray(std::vector<light_t*> lights, std::vector<triangle_t*> triangles, triangle_t triangle, vector3_t viewDirectionVector, vector3_t surfaceNormal, vector3_t surfaceIntersectionVector, float distanceFromCamera, sceneSpecs_t specs) {
	vector3_t ambientIlluminationColor, diffuseIlluminationColor, specularIlluminationColor, ligthDirectionVector, hVector;
	color_t diffuseColor;
	ray_t shadowOriginRay;
	float shadowFlag, attentuationFactor, distanceToLight;

	if(triangle.isTextured) {
		vector3_t coordinates = getBarycentricCoordinates(surfaceIntersectionVector, triangle, specs.vertices);
		textureCoordinate_t* vertexCoordinate0 = specs.textureCoordinates.at(triangle.textureCoordinatesIndices[0]);
		textureCoordinate_t* vertexCoordinate1 = specs.textureCoordinates.at(triangle.textureCoordinatesIndices[1]);
		textureCoordinate_t* vertexCoordinate2 = specs.textureCoordinates.at(triangle.textureCoordinatesIndices[2]);
		 
		float u = coordinates.z * vertexCoordinate0->u + coordinates.x * vertexCoordinate1->u + coordinates.y * vertexCoordinate2->u;
		float v = coordinates.z * vertexCoordinate0->v + coordinates.x * vertexCoordinate1->v + coordinates.y * vertexCoordinate2->v;
		
		diffuseColor = getTextureColor(u, v, triangle.texture);
	} else {
		diffuseColor = triangle.materialColor->diffuseColor;
	}

	// set initial illumination to ambient 
	vector3_t illuminationColor = multiplyCoefficient(colorToVector(diffuseColor), triangle.materialColor->ambient);  

	// loop over every light and add its illumination and calculate its shadow flag
	for(int i = 0; i < lights.size(); i++) {
		ligthDirectionVector = lights.at(i)->w == 1.0 ? normalize(subtractVectors(lights.at(i)->vector, surfaceIntersectionVector)) : normalize(negative(lights.at(i)->vector)); 
		hVector = normalize(averageVector(ligthDirectionVector, viewDirectionVector));
		
		shadowOriginRay.position = surfaceIntersectionVector;
		shadowOriginRay.direction = ligthDirectionVector;
		shadowFlag = getSampledShadowFlag(shadowOriginRay, specs.spheres, triangles, specs.vertices, specs.normals, surfaceIntersectionVector, lights.at(i)->vector, lights.at(i)->w, 100);

		distanceToLight = vectorDistance(lights.at(i)->vector, surfaceIntersectionVector);
		attentuationFactor = lights.at(i)->w == 1.0 ? 1.0 / (lights.at(i)->c1 + (lights.at(i)->c2 * distanceToLight) + (lights.at(i)->c3 * distanceToLight * distanceToLight)) : 1.0;
		
		diffuseIlluminationColor = multiplyCoefficient(multiplyCoefficient(colorToVector(diffuseColor), triangle.materialColor->diffuse), std::max(0.0f, dotProduct(surfaceNormal, ligthDirectionVector)));
		specularIlluminationColor = multiplyCoefficient(multiplyCoefficient(colorToVector(triangle.materialColor->specularColor), triangle.materialColor->specular), float(pow(std::max(0.0f, dotProduct(surfaceNormal, hVector)), triangle.materialColor->specularFalloff))); 
		illuminationColor = addVectors(illuminationColor, multiplyCoefficient(multiplyCoefficient(multiplyVectors(colorToVector(lights.at(i)->color), addVectors(diffuseIlluminationColor, specularIlluminationColor)), shadowFlag), attentuationFactor));
	}
	
	// determine depthcue alpha
	float alphaDepthcue;
	if(distanceFromCamera <= specs.dNear) {
		alphaDepthcue = specs.alphaMax;
	} else if(distanceFromCamera >= specs.dFar) {
		alphaDepthcue = specs.alphaMin;
	} else {
		alphaDepthcue = specs.alphaMin + (specs.alphaMax - specs.alphaMin) * ((specs.dFar - distanceFromCamera) / (specs.dFar - specs.dNear));
	}

	// return color with depthcue weight applied
	return vectorToColor(addVectors(multiplyCoefficient(clampVector(illuminationColor, 1, 1, 1), alphaDepthcue), multiplyCoefficient(colorToVector(specs.depthcueColor), 1.0 - alphaDepthcue)));
}

// returns color_t traced from ray to object or background
color_t traceRay(ray_t& ray, sceneSpecs_t specs) {
    sphere_t clostestSphere;
	float distance, closestSphereDistance = std::numeric_limits<float>::max();
    for(int i = 0; i < specs.spheres.size(); i++) {
		distance = intersectsSphere(ray, *(specs.spheres.at(i)));
        
		if(distance >= 0 && distance < closestSphereDistance) {
			clostestSphere = *(specs.spheres.at(i));
			closestSphereDistance = distance;
		}
    }

	triangle_t closestTriangle;
	vector3_t surfaceNormal, closestNormal;
	float closestTriangleDistance = std::numeric_limits<float>::max();
	for(int i = 0; i < specs.triangles.size(); i++) {
		distance = intersectsTriangle(ray, *(specs.triangles.at(i)), specs.vertices, specs.normals, &surfaceNormal);
       
		if(distance >= 0 && distance < closestTriangleDistance) {
			closestTriangle = *(specs.triangles.at(i));
			closestTriangleDistance = distance;
			closestNormal = surfaceNormal;
		}
    }

	if((closestSphereDistance == std::numeric_limits<float>::max() || closestSphereDistance == std::numeric_limits<double>::infinity()) &&
	   (closestTriangleDistance == std::numeric_limits<float>::max() || closestTriangleDistance == std::numeric_limits<double>::infinity())) {
		return specs.backgroundColor;
	}

	if(closestSphereDistance < closestTriangleDistance) {
		vector3_t intersectionPosition = addVectors(multiplyCoefficient(ray.direction, closestSphereDistance), ray.position);
		/*if(vectorDistance(clostestSphere.position, intersectionPosition) > clostestSphere.radius) {
			std::cout << "distance to center: " << vectorDistance(clostestSphere.position, intersectionPosition) << std::endl;
		}*/
		
    	return shade_ray(specs.lights, specs.spheres, clostestSphere, negative(ray.direction), intersectionPosition, closestSphereDistance, specs);
	}

	vector3_t intersectionPosition = addVectors(multiplyCoefficient(ray.direction, closestTriangleDistance), ray.position);
    return shade_ray(specs.lights, specs.triangles, closestTriangle, negative(ray.direction), closestNormal, intersectionPosition, closestTriangleDistance, specs);
}

int main(int argc, char** argv) {
	// seed random generator
	srand(time(0));

	std::string filename;
    sceneSpecs_t sceneSpecs = getSceneSpecifications(argc, argv, filename);
	
    // if scene specifications were not valid, stop execution
    if(!sceneSpecs.wellFormed) {
    	return -1;
    }

    // if up vector is equal to view direction vector, nudge to prevent divide by zero
    if(vectorsEqual(sceneSpecs.upVector, sceneSpecs.viewDirectionVector)) {
    	sceneSpecs.viewDirectionVector.x += DELTA;
		sceneSpecs.viewDirectionVector.y += DELTA;
		sceneSpecs.viewDirectionVector.z += DELTA;
    }

	// precalculate e1, e2 and normal of flat shaded triangle
	triangle_t* triangle;
	for(int i = 0; i < sceneSpecs.triangles.size(); i ++) {
		triangle = sceneSpecs.triangles.at(i);
		triangle->e1 = subtractVectors(*sceneSpecs.vertices.at(triangle->pointIndices[1]), *sceneSpecs.vertices.at(triangle->pointIndices[0]));
		triangle->e2 = subtractVectors(*sceneSpecs.vertices.at(triangle->pointIndices[2]), *sceneSpecs.vertices.at(triangle->pointIndices[0]));

		triangle->normal = normalize(crossProduct(triangle->e1, triangle->e2));
	}

    color_t** pixels = (color_t**) malloc(sizeof(color_t*) * sceneSpecs.imageHeight); 
    ray_t** rays = (ray_t**) malloc(sizeof(ray_t*) * sceneSpecs.imageHeight); 

	for(int i = 0; i < sceneSpecs.imageHeight; i++) {
		pixels[i] = (color_t*) malloc(sizeof(color_t) * sceneSpecs.imageWidth);
		rays[i] = (ray_t*) malloc(sizeof(ray_t) * sceneSpecs.imageWidth);
	}
	
	float aspectRatio = (sceneSpecs.imageWidth * 1.0) / (sceneSpecs.imageHeight * 1.0);
	float viewWindowWidth = getViewWindowWidth(sceneSpecs.horizontalFOV);
	float viewWindowHeight = getViewWindowHeight(viewWindowWidth, aspectRatio);
	
    makeRays(rays, sceneSpecs, viewWindowWidth, viewWindowHeight);

    // trace rays in scene
	for(int row = 0; row < sceneSpecs.imageHeight; row++) {
        for(int col = 0; col < sceneSpecs.imageWidth; col++) {
            pixels[row][col] = traceRay(rays[row][col], sceneSpecs);
        }
    }

    writePPMFile(filename, pixels, sceneSpecs.imageWidth, sceneSpecs.imageHeight);

	for(int i = 0; i < sceneSpecs.imageHeight; i++) {
		free(pixels[i]);
		free(rays[i]);
	}

	for(int i = 0; i < sceneSpecs.spheres.size(); i++) {
		free(sceneSpecs.spheres.at(i));
	}

	//TODO fix free
	/*for(int i = 0; i < sceneSpecs.spheres.size(); i++) {
		free(sceneSpecs.materialColors.at(i));
	}*/

	free(pixels);
	free(rays);
	
	return 0;
}
