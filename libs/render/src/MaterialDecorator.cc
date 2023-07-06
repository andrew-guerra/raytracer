#include "../include/MaterialDecorator.h"
#include <iostream>

MaterialDecorator::MaterialDecorator(SceneEntity* entity, float ambient, float diffuse, float specular, float specularFalloff) {
    this->entity = entity;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->specularFalloff = specularFalloff;
}

float MaterialDecorator::intersectionDistance(Ray* ray) {
    return this->entity->intersectionDistance(ray);
}

Color* MaterialDecorator::getPointColor(Vector3* intersectionPoint, Vector3* cameraDirectionVector, std::vector<SceneEntity*> lights) {
    Color entityColor = *this->entity->getPointColor(intersectionPoint, cameraDirectionVector, lights);
    Color* illuminationColor = new Color(entityColor * this->ambient);

    for(int i = 0; i < lights.size(); i++) {
        Vector3 lightDirectionVector = *lights.at(i)->getPosition() - *intersectionPoint;
        lightDirectionVector.noramlize();

        Vector3 hVector = lightDirectionVector.average(*cameraDirectionVector);
        hVector.noramlize();

        Vector3 surfaceNormal = this->getSurfaceNormal(intersectionPoint);

        *illuminationColor += (entityColor * this->diffuse) * std::max(surfaceNormal.dotProduct(lightDirectionVector), 0.0f);
        *illuminationColor += (WHITE * this->diffuse) * pow(std::max(surfaceNormal.dotProduct(hVector), 0.0f), this->specularFalloff);
    }

    return illuminationColor;
}

Vector3 MaterialDecorator::getSurfaceNormal(Vector3* intersectionPoint) {
    return this->entity->getSurfaceNormal(intersectionPoint);
}