#include "../include/SceneEntityBaseDecorator.h"

SceneEntityBaseDecorator::SceneEntityBaseDecorator(SceneEntity* entity) {
    this->entity = entity;
}

SceneEntityBaseDecorator::SceneEntityBaseDecorator() {
    this->entity = nullptr;
}

float SceneEntityBaseDecorator::intersectionDistance(Ray* ray) {
    return this->entity->intersectionDistance(ray);
}

const Color* SceneEntityBaseDecorator::getPointColor(Vector3* intersectionPoint) {
    return this->entity->getPointColor(intersectionPoint);
}