#include "../include/Scene.h"

Scene::Scene(std::vector<SceneEntity*>& entities, std::vector<SceneEntity*> lights, Color* backgroundColor) {
    this->entities = entities;
    this->lights = lights;
    this->backgroundColor = backgroundColor;
}

Scene::Scene() {
    this->entities = std::vector<SceneEntity*>();
    this->lights = std::vector<SceneEntity*>();
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

std::vector<SceneEntity*> Scene::getLights() {
    return this->lights;
}

int Scene::getNumLights() {
    return this->lights.size();
}

Color* Scene::getBackgroundColor() {
    return this->backgroundColor;
}