#ifndef CONSOLE_RENDER_PROGRESS_TRACKER_DECORATOR_H
#define CONSOLE_RENDER_PROGRESS_TRACKER_DECORATOR_H

#include "RenderProgressTrackerDecorator.h"
#include <iostream>

/**
 * @class RenderProgressTrackerDecorator
 * @brief Decorates a SceneRenderer with a progress tracker of the rendered scene
 * 
 * A RenderProgressTrackerDecorator is a decorator class for a SceneRenderer object. It will display
 * the progress a renderer has made in rendering a scene.
*/
class ConsoleRenderProgressTrackerDecorator : public RenderProgressTrackerDecorator {
    public:
        /**
         * @brief Constructor assigns renderer to ConsoleRenderProgressTrackerDecorator object
         * @param renderer The renderer wrapped by the ConsoleRenderProgressTrackerDecorator object
        */
        ConsoleRenderProgressTrackerDecorator(SceneRenderer* renderer);

        virtual void displayRenderMetrics();
        virtual void displayProgress();
        virtual Color** renderScene();
};

#endif