#include "../include/Camera.h"
#include "../../math/include/Ray.h"

Camera::Camera(Ray* cameraRay, Vector3* upVector, float hfov, float vfov) {
    this->cameraRay = cameraRay;
    this->upVector = upVector;
    this->hfov = hfov;
    this->vfov = vfov;
}

Camera::Camera() {
    this->cameraRay = new Ray(new Vector3(0, 0, 0), new Vector3(0, 0, -1));
    this->upVector = new Vector3(0, 1, 0);
    this->hfov = 120;
    this->vfov = 60;
}

Camera::~Camera() {
    delete this->cameraRay;
    delete this->upVector;
}

Ray* Camera::getCameraRay() {
    return this->cameraRay;
}

Vector3* Camera::getUpVector() {
    return this->upVector;
}

float Camera::getHorizontalFOV() {
    return this->hfov;
}

float Camera::getVerticalFOV() {
    return this->vfov;
}

Camera DEFAULT_CAMERA = Camera();