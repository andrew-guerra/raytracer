#ifndef MATERIAL_DECORATOR_H
#define MATERIAL_DECORATOR_H

#include "SceneEntityBaseDecorator.h"

/**
 * @class BumpmapDecorator
 * @brief Represents an bumpmap for a SceneEntity object
 * 
 * A BumpmapDecorator object is a representation of a bumpmap for a SceneEntity object. 
 * The bumpmap affects the normals of the SceneEntity object and by proxy, the intersection function. 
 * It has all of the properties of a SceneEntity object.
*/
class BumpmapDecorator : public SceneEntityBaseDecorator {
    public:
        /**
         * @brief Constructor assigns entity to BumpmapDecorator object
         * @param entity The entity wrapped by the BumpmapDecorator object
        */
        BumpmapDecorator(SceneEntity* entity);
};

#endif