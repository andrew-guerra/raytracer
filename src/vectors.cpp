#include <cmath>
#include <string>

#include "vectors.h"

float magnitude(vector3_t vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float vectorDistance(vector3_t v1, vector3_t v2) {
    return magnitude(subtractVectors(v1, v2));
}

float sumVector(vector3_t vector) {
    return vector.x + vector.y + vector.z;
}

vector3_t normalize(vector3_t vector) {
    vector3_t normalizedVector;

    float size = magnitude(vector);
    normalizedVector.x = vector.x / size;
    normalizedVector.y = vector.y / size;
    normalizedVector.z = vector.z / size;

    return normalizedVector;
}

vector3_t negative(vector3_t vector) {
    return multiplyCoefficient(vector, -1.0);
}

vector3_t roundVector(vector3_t vector) {
    vector3_t roundedVector;

    roundedVector.x = (int) round(vector.x);
    roundedVector.y = (int) round(vector.y);
    roundedVector.z = (int) round(vector.z);

    return roundedVector;
}
vector3_t crossProduct(vector3_t v1, vector3_t v2) {
    vector3_t productVector;

    productVector.x = v1.y * v2.z - v1.z * v2.y;
    productVector.y = v1.z * v2.x - v1.x * v2.z ; 
    productVector.z = v1.x * v2.y - v1.y * v2.x;

    return productVector;
}

float dotProduct(vector3_t v1, vector3_t v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vector3_t multiplyVectors(vector3_t v1, vector3_t v2) {
    vector3_t productVector;

    productVector.x = v1.x * v2.x;
    productVector.y = v1.y * v2.y;
    productVector.z = v1.z * v2.z;

    return productVector;
}

vector3_t subtractVectors(vector3_t v1, vector3_t v2) {
    vector3_t result;

    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;

    return result;
}

vector3_t addVectors(vector3_t v1, vector3_t v2) {
    vector3_t result;

    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;

    return result;
}

vector3_t multiplyCoefficient(vector3_t vector, float coefficient) {
    vector3_t result;
    result.x = vector.x * coefficient;
    result.y = vector.y * coefficient;
    result.z = vector.z * coefficient;

    return result;
}

bool vectorsEqual(vector3_t v1, vector3_t v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

std::string vectorToString(vector3_t vector) {
    return "(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ", " + std::to_string(vector.z) + ")";
}

vector3_t colorToVector(color_t color) {
    vector3_t vector;

    vector.x = color.red;
    vector.y = color.green;
    vector.z = color.blue;

    return vector;
}

color_t vectorToColor(vector3_t vector) {
    color_t color;

    color.red = vector.x;
    color.green = vector.y;
    color.blue = vector.z;

    return color;
}

vector3_t maxVector(vector3_t v1, vector3_t v2) {
    vector3_t vector;

    vector.x = std::max(v1.x, v2.x);
    vector.y = std::max(v1.y, v2.y);
    vector.z = std::max(v1.z, v2.z);

    return vector;
}

vector3_t clampVector(vector3_t vector, float xMax, float yMax, float zMax) {
    vector3_t clampedVector;
    
    clampedVector.x = std::min(vector.x, xMax);
    clampedVector.y = std::min(vector.y, yMax);
    clampedVector.z = std::min(vector.z, zMax);

    return clampedVector;
}

vector3_t averageVector(vector3_t v1, vector3_t v2) {
    vector3_t vector;

    vector.x = (v1.x + v2.x) / 2.0;
    vector.y = (v1.y + v2.y) / 2.0;
    vector.z = (v1.z + v2.z) / 2.0;;

    return vector;
}

vector3_t squareVector(vector3_t vector) {
    vector3_t squareVector;

    squareVector.x = squareVector.x * squareVector.x;
    squareVector.y = squareVector.y * squareVector.y;
    squareVector.z = squareVector.z * squareVector.z;

    return squareVector;
}