#ifndef LIGHT_DECORATOR_H
#define LIGHT_DECORATOR_H

#include "SceneEntityBaseDecorator.h"

/**
 * @class LightDecorator
 * @brief Represents an light surface for a SceneEntity object
 * 
 * A LightDecorator object is a representation of a light surface for a SceneEntity object. 
 * The light will cover the exterior of the SceneEntity object and the normals of the object
 * will be the direction of the light rays. It has all of the properties of a SceneEntity object.
*/
class LightDecorator : public SceneEntityBaseDecorator {
    public:
        /**
         * @brief Constructor assigns entity to LightDecorator object
         * @param entity The entity wrapped by the LightDecorator object
        */
        LightDecorator(SceneEntity* entity);
};

#endif