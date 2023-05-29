#include "../include/Sphere.h"

Sphere::Sphere(Vector3* center, double radius) : SceneEntity(center) {
    this->radius = radius;
}

float Sphere::intersectionDistance(Ray* ray) {
    Vector3 diffVector = *ray->getOrigin() - *this->getPosition();

    float A = ray->getDirection()->dotProduct(&(ray->getDirection()));
    float B = 2.0 * ray->getDirection()->dotProduct(diffVector);
    float C = diffVector.dotProduct(diffVector) - (this->radius * this->radius);
    float discriminate = (B * B) - (4 * A * C);

    // no intersection
    if(discriminate <= 0) {
        return std::numeric_limits<double>::infinity();
    }

    float discriminateSqrt = sqrt(discriminate);
    float firstIntersection = (-B - discriminateSqrt) / (2 * A);
    float secondIntersection = (-B + discriminateSqrt) / (2 * A);

    // intersections behind the origin
    if(std::max(firstIntersection, secondIntersection) < 0) {
		return -1;
	}

    return std::min(firstIntersection, secondIntersection);
}

const Color* Sphere::getPointColor(Vector3* intersectionPoint) {
    return &RED;
}