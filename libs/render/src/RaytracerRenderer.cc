#include "../include/RaytracerRenderer.h"
#include <iostream>

RaytracerRenderer::RaytracerRenderer(Scene* scene, Camera* camera, int imageWidth, int imageHeight, float viewDistance) : SceneRenderer(scene, camera, imageWidth, imageHeight) {
    this->viewDistance = viewDistance;
    this->viewWindowWidth = 2 * viewDistance * std::tan(camera->getHorizontalFOV() * PI / 180.0 * 0.5f);
    this->viewWindowHeight = 2 * viewDistance * std::tan(camera->getVerticalFOV() * PI / 180.0 * 0.5f);
    this->currRow = 0;
    this->currCol = 0;
}

Color** RaytracerRenderer::renderScene() {
    this->rays = generateRays();
    Color** pixelColors = generatePixelColors();

    for(this->currRow = 0; this->currRow < this->imageHeight; this->currRow++) {
        for(this->currCol = 0; this->currCol < this->imageWidth; this->currCol++) {
            pixelColors[this->currRow][this->currCol] = *traceRay(rays[this->currRow][this->currCol]);
        }
    }

    return pixelColors;
}

float RaytracerRenderer::getPercentageSceneRendered() {
    return ((this->currRow * this->imageWidth) + (this->currCol + 1)) / (this->imageHeight * this->imageWidth);
}

Ray** RaytracerRenderer::generateRays() {
    Vector3 uVector = this->camera->getCameraRay()->getDirection()->crossProduct(*this->camera->getUpVector());
    uVector.noramlize();

    Vector3 vVector = uVector.crossProduct(*this->camera->getCameraRay()->getDirection());
    vVector.noramlize();

    Vector3 viewWindowVector = *this->camera->getCameraRay()->getOrigin() + (*this->camera->getCameraRay()->getDirection() * viewDistance);
    Vector3 uPrimeVector = uVector * (this->viewWindowWidth / 2); 
    Vector3 vPrimeVector = vVector * (this->viewWindowHeight / 2); 

    Vector3 ulVector = viewWindowVector - uPrimeVector + vPrimeVector;
    Vector3 urVector = viewWindowVector + uPrimeVector + vPrimeVector;
    Vector3 llVector = viewWindowVector - uPrimeVector - vPrimeVector;
    Vector3 lrVector = viewWindowVector + uPrimeVector - vPrimeVector;

    Vector3 deltaH = (urVector - ulVector) / (this->imageWidth - 1);
    Vector3 deltaV = (llVector - ulVector) / (this->imageHeight - 1);

    Ray** rays = (Ray**) malloc(sizeof(Ray*) * this->imageHeight); 

	for(int i = 0; i < this->imageHeight; i++) {
		rays[i] = (Ray*) malloc(sizeof(Ray) * this->imageWidth);
	}

    Vector3 fullDeltaH, fullDeltaV, viewWindowPixelVector;
    Vector3* rayOrigin;
    Vector3* rayDirection;

    for(int row = 0; row < this->imageHeight; row++) {
        fullDeltaV = deltaV * row;
        
        for(int col = 0; col < this->imageWidth; col++) {
            fullDeltaH = deltaH * col;
            viewWindowPixelVector = ulVector + fullDeltaV + fullDeltaH;

            rayOrigin = (Vector3*) malloc(sizeof(Vector3));
            *rayOrigin = *this->camera->getCameraRay()->getOrigin();

            rayDirection = (Vector3*) malloc(sizeof(Vector3));
            *rayDirection = viewWindowPixelVector - *rayOrigin;
            rayDirection->noramlize();

            rays[row][col] = Ray(rayOrigin, rayDirection);
        }
    }
    
    return rays;
}

Color** RaytracerRenderer::generatePixelColors() {
    Color** pixelColors = (Color**) malloc(sizeof(Color*) * this->imageHeight);

    for(int i = 0; i < this->imageHeight; i++) {
		pixelColors[i] = (Color*) malloc(sizeof(Color) * this->imageWidth);
	}

    return pixelColors;
}

Color* RaytracerRenderer::traceRay(Ray ray) {
    SceneEntity* closestEntity = getClosestEntity(ray);

    if(closestEntity == nullptr) {
        return scene->getBackgroundColor();
    }

    float closestDistance = closestEntity->intersectionDistance(&ray);
    Vector3 intersectionPoint = this->camera->getCameraRay()->getMemberPoint(closestDistance);
    Vector3 cameraDirectionVector = -(*ray.getDirection());
    
    return closestEntity->getPointColor(&intersectionPoint, &cameraDirectionVector, this->scene->getLights());
}

float RaytracerRenderer::getShadowFlag(Ray ray) {
    SceneEntity* closestEntity = getClosestEntity(ray);

    if(closestEntity == nullptr) {
        return 1;
    }

    float closestDistance = closestEntity->intersectionDistance(&ray);
    Vector3 intersectionPoint = this->camera->getCameraRay()->getMemberPoint(closestDistance);

    return 1;
}

SceneEntity* RaytracerRenderer::getClosestEntity(Ray ray) {
    std::vector<SceneEntity*> sceneEntities = this->scene->getEntities();
    SceneEntity* closestEntity = nullptr;
    float closestDistance = std::numeric_limits<float>::max();
    float intersectionDistance;

    for(SceneEntity* entity : sceneEntities) {
        intersectionDistance = entity->intersectionDistance(&ray);

        if(intersectionDistance < closestDistance && intersectionDistance >= EPLSION) {
            closestEntity = entity;
            closestDistance = intersectionDistance;
        }
    }

    return closestEntity;
}