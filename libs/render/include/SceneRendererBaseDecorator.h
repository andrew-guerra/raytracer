#ifndef SCENE_RENDERER_BASE_DECORATOR_H
#define SCENE_RENDERER_BASE_DECORATOR_H

#include "SceneRenderer.h"

/**
 * @class SceneRendererBaseDecorator
 * @brief Represents an decorator for a SceneRenderer object
 * 
 * A SceneRendererBaseDecorator object is a representation of a decorator for a SceneRenderer object. 
 * It has all of the properties of a SceneEntity object.
*/
class SceneRendererBaseDecorator : public SceneRenderer {
    public:
        /**
         * @brief Constructor assigns entity to SceneRendererBaseDecorator object
         * @param renderer The renderer wrapped by the SceneRendererBaseDecorator object
        */
        SceneRendererBaseDecorator(SceneRenderer* renderer);

        /**
         * @brief Constructor for SceneRendererBaseDecorator object
        */
        SceneRendererBaseDecorator();

        virtual Color** renderScene();
        virtual float getPercentageSceneRendered();
        
    protected:
        SceneRenderer* renderer;
};

#endif
