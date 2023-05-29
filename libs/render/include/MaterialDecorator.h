#ifndef MATERIAL_DECORATOR_H
#define MATERIAL_DECORATOR_H

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
        MaterialDecorator(SceneEntity* entity);
};

#endif