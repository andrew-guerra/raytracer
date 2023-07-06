#ifndef RENDER_PROGRESS_TRACKER_DECORATOR_H
#define RENDER_PROGRESS_TRACKER_DECORATOR_H

#include "SceneRendererBaseDecorator.h"

/**
 * @class RenderProgressTrackerDecorator
 * @brief Decorates a SceneRenderer with a progress tracker of the rendered scene
 * 
 * A RenderProgressTrackerDecorator is a decorator class for a SceneRenderer object. It will display
 * the progress a renderer has made in rendering a scene.
*/
class RenderProgressTrackerDecorator : public SceneRendererBaseDecorator {
    public:
        /**
         * @brief Constructor assigns entity to RenderProgressTrackerDecorator object
         * @param renderer The renderer wrapped by the RenderProgressTrackerDecorator object
        */
        RenderProgressTrackerDecorator(SceneRenderer* renderer);

        /**
         * @brief Defualt constructor for RenderProgressTrackerDecorator object
        */
        RenderProgressTrackerDecorator();

        /**
         * @brief Displays a description of the rendering image (size)
        */
        virtual void displayRenderMetrics() = 0;

        /**
         * @brief Displays the progress of the rendered scene
        */
        virtual void displayProgress() = 0;
        
        virtual Color** renderScene();
};

#endif
