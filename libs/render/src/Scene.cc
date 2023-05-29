#include "../include/Scene.h"

Scene::Scene(SceneEntity* entities) {
    this->entities = entities;
}

Scene::Scene() {
    this->entities = nullptr;
}

Scene::~Scene() {
    delete this->entities;
}