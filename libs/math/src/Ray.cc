#include "../include/Ray.h"

Ray::Ray(Vector3* origin, Vector3* direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray::Ray() {
    this->origin = new Vector3();
    this->direction = new Vector3();
}

Ray::Ray(const Ray& copyRay) {
    this->origin = copyRay.origin;
    this->direction = copyRay.direction;
}

Ray::~Ray() {
    delete this->origin;
    delete this->direction;
}

Vector3* Ray::getOrigin() {
    return this->origin;
}

Vector3* Ray::getDirection() {
    return this->direction;
}

Vector3 getDirection();

Vector3 Ray::getMemberPoint(float scaler) {
    return *this->origin + (*this->direction * scaler);
}

void Ray::scale(float scaler) {
    this->direction->multiplyCoefficient(scaler);
}

void Ray::rotate(float xTheta, float yTheta, float zTheta) {
    Vector3 directionRotated(this->direction->getX(), this->direction->getY() * std::cos(xTheta) - this->direction->getZ() * std::sin(xTheta), this->direction->getY() * std::sin(xTheta) + this->direction->getZ() * std::cos(xTheta));
    directionRotated = Vector3(this->direction->getX() * std::cos(yTheta) + this->direction->getZ() * std::sin(yTheta), this->direction->getY(), -this->direction->getX() * std::sin(yTheta) + this->direction->getZ() * std::cos(xTheta));
    directionRotated = Vector3(this->direction->getX() * std::cos(zTheta) - this->direction->getY() * std::sin(zTheta), this->direction->getX() * std::sin(zTheta) + this->direction->getY() * std::cos(zTheta), this->direction->getZ());

    this->direction = &directionRotated;
}

void Ray::translate(Vector3 translationVec){
    this->origin->add(translationVec);
}