#include "../include/SceneEntity.h"

SceneEntity::SceneEntity(Vector3* position) {
    this->position = position;
}

SceneEntity::SceneEntity() {
    this->position = nullptr;
}

SceneEntity::~SceneEntity() {
    delete this->position;
}

Vector3* SceneEntity::getPosition() {
    return this->position;
}

void SceneEntity::setPosition(Vector3* position) {
    this->position = position;
}