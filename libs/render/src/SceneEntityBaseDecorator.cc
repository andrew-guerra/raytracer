#include "../include/SceneEntityBaseDecorator.h"

SceneEntityBaseDecorator::SceneEntityBaseDecorator(SceneEntity* entity) {
    this->entity = entity;
}

SceneEntityBaseDecorator::SceneEntityBaseDecorator() {
    this->entity = nullptr;
}

Vector3* SceneEntityBaseDecorator::getPosition() {
    return this->entity->getPosition();
}

float SceneEntityBaseDecorator::intersectionDistance(Ray* ray) {
    return this->entity->intersectionDistance(ray);
}

Color* SceneEntityBaseDecorator::getPointColor(Vector3* intersectionPoint, Vector3* cameraDirectionVector, std::vector<SceneEntity*> lights) {
    return this->entity->getPointColor(intersectionPoint, cameraDirectionVector, lights);
}

Vector3 SceneEntityBaseDecorator::getSurfaceNormal(Vector3* intersectionPoint) {
    return Vector3(0, 1, 0);
}