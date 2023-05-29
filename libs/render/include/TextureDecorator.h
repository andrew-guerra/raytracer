#ifndef TEXTURE_DECORATOR_H
#define TEXTURE_DECORATOR_H

#include "SceneEntityBaseDecorator.h"

/**
 * @class TextureDecorator
 * @brief Represents an texture for a SceneEntity object
 * 
 * A TextureDecorator object is a representation of a texture for a SceneEntity object. 
 * The texture affects the color of the SceneEntity object via a texture map. It has 
 * all of the properties of a SceneEntity object.
*/
class TextureDecorator : public SceneEntityBaseDecorator {
    public:
        /**
         * @brief Constructor assigns entity to TextureDecorator object
         * @param entity The entity wrapped by the TextureDecorator object
        */
        TextureDecorator(SceneEntity* entity);
};

#endif