#ifndef SCENE_ENTITY_BASE_DECORATOR_H
#define SCENE_ENTITY_BASE_DECORATOR_H

#include "SceneEntity.h"

/**
 * @class SceneEntityBaseDecorator
 * @brief Represents an decorator for a SceneEntity object
 * 
 * A SceneEntityBaseDecorator object is a representation of a decorator for a SceneEntity object. 
 * The decorator can affect the intersection function of SceneEntity (such as applying a bump map).
 * It decorator can also affect the color function (such as applying a texture map). It has all of 
 * the properties of a SceneEntity object.
*/
class SceneEntityBaseDecorator : public SceneEntity {
    public:
        /**
         * @brief Constructor assigns entity to SceneEntityBaseDecorator object
         * @param entity The entity wrapped by the SceneEntityBaseDecorator object
        */
        SceneEntityBaseDecorator(SceneEntity* entity);

        /**
         * @brief Constructor for SceneEntityBaseDecorator object
        */
        SceneEntityBaseDecorator();

        virtual float intersectionDistance(Ray* ray);
        virtual const Color* getPointColor(Vector3* intersectionPoint);
        
    protected:
        SceneEntity* entity;
};

#endif