#ifndef MATERIAL_DECORATOR_H
#define MATERIAL_DECORATOR_H

#include <math.h>

#include "SceneEntityBaseDecorator.h"

/**
 * @class MaterialDecorator
 * @brief Represents an material for a SceneEntity object
 * 
 * A MaterialDecorator object is a representation of a material for a SceneEntity object. 
 * The material affects the base color of the SceneEntity object as well as how light interacts with it. 
 * It has all of the properties of a SceneEntity object.
*/
class MaterialDecorator : public SceneEntityBaseDecorator {
    public:
        /**
         * @brief Constructor assigns entity to MaterialDecorator object
         * @param entity The entity wrapped by the MaterialDecorator object
        */
        MaterialDecorator(SceneEntity* entity, float ambient, float diffuse, float specular, float specularFalloff);

        virtual float intersectionDistance(Ray* ray);
        virtual Color* getPointColor(Vector3* intersectionPoint, Vector3* cameraDirectionVector, std::vector<SceneEntity*> entities);
        virtual Vector3 getSurfaceNormal(Vector3* intersectionPoint);

    private:
        float ambient;
        float diffuse;
        float specular;
        float specularFalloff;
};

#endif