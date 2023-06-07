#include "../include/Scene.h"

Scene::Scene(std::vector<SceneEntity*>& entities, const Color* getBackgroundColor) {
    this->entities = entities;
    this->backgroundColor = backgroundColor;
}

Scene::Scene() {
    this->entities = std::vector<SceneEntity*>();
    this->backgroundColor = &BLACK;
}

Scene::~Scene() {

}

std::vector<SceneEntity*> Scene::getEntities() {
    return this->entities;
}

int Scene::getNumEntities() {
    return this->entities.size();
}

const Color* Scene::getBackgroundColor() {
    return this->backgroundColor;
}