#ifndef VECTORS_H
#define VECTORS_H

#include <string>
#include "types.h"

// struct for 3D vector
/*typedef struct {
    float x, y, z;
} vector3_t;*/

float magnitude(vector3_t vector);
float vectorDistance(vector3_t v1, vector3_t v2);
float sumVector(vector3_t vector);
vector3_t normalize(vector3_t vector);
vector3_t negative(vector3_t vector);
vector3_t roundVector(vector3_t vector);
vector3_t crossProduct(vector3_t v1, vector3_t v2);
float dotProduct(vector3_t v1, vector3_t v2);
vector3_t multiplyVectors(vector3_t v1, vector3_t v2);
vector3_t subtractVectors(vector3_t v1, vector3_t v2);
vector3_t addVectors(vector3_t v1, vector3_t v2);
vector3_t multiplyCoefficient(vector3_t vector, float coefficient);
bool vectorsEqual(vector3_t v1, vector3_t v2);
std::string vectorToString(vector3_t vector);
vector3_t colorToVector(color_t color);
vector3_t maxVector(vector3_t v1, vector3_t v2);
vector3_t averageVector(vector3_t v1, vector3_t v2);
vector3_t squareVector(vector3_t vector);
vector3_t clampVector(vector3_t vector, float xMax, float yMax, float zMax);
color_t vectorToColor(vector3_t vector);

#endif
