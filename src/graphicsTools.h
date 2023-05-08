#ifndef GRAPHICSTOOLS_H
#define GRAPHICSTOOLS_H

#include <vector>
#include "types.h"

// struct for color
/*typedef struct color {
    int red, green, blue;
} color_t;*/

typedef struct {
	color_t diffuseColor, specularColor;
	float ambient, diffuse, specular, specularFalloff;
} materialColor_t;

typedef struct {
	color_t** textureColors;
	float width, height;
} texture_t;

typedef struct {
	float u, v;
} textureCoordinate_t;

typedef struct {
	vector3_t vector;
	color_t color;
	float w, c1, c2, c3;
} light_t;

// struct for cylinder
typedef struct {
	vector3_t position, direction;
	float radius, length;
	color_t materialColor;
	int materialColorIndex;
} cyldiner_t;

// struct for sphere
typedef struct {
	vector3_t position;
	bool isTextured;
	float radius;
	materialColor_t* materialColor;
	texture_t* texture;
	int materialColorIndex, textureIndex;
} sphere_t;

// struct for triangle
typedef struct {
	bool isTextured;
	vector3_t e1, e2, normal;
	int pointIndices[3];
	int normalIndices[3];
	int textureCoordinatesIndices[3];
	materialColor_t* materialColor;
	texture_t* texture;
} triangle_t;

// struct for ray
typedef struct {
    vector3_t position, direction;
} ray_t;

// struct for specfications of a scene
typedef struct {
	vector3_t viewOriginVector, viewDirectionVector, upVector;
	int imageWidth, imageHeight;
	float horizontalFOV, dNear, dFar, alphaMin, alphaMax;
	color_t backgroundColor, depthcueColor;
	std::vector<materialColor_t*> materialColors;
	std::vector<sphere_t*> spheres;
	std::vector<triangle_t*> triangles;
	std::vector<vector3_t*> vertices;
	std::vector<vector3_t*> normals;
	std::vector<light_t*> lights;
	std::vector<texture_t*> textures;
	std::vector<textureCoordinate_t*> textureCoordinates;
	bool wellFormed; // flag for if stuct was well formed from input file
	bool isParallel; // flag for parallel projection
} sceneSpecs_t;

#endif
