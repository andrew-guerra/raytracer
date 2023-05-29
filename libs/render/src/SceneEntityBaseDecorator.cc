#include "../include/SceneEntityBaseDecorator.h"

SceneEntityBaseDecorator::SceneEntityBaseDecorator(SceneEntity* entity) {
    this->entity = entity;
}

SceneEntityBaseDecorator::SceneEntityBaseDecorator() {
    this->entity = nullptr;
}