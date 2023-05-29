#include "../include/Sphere.h"

Sphere::Sphere(Vector3* center, double radius) : SceneEntity(center) {
    this->radius = radius;
}