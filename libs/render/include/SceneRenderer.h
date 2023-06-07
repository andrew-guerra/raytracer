#ifndef SCENE_RENDERER_H
#define SCENE_RENDERER_H

#include "Scene.h"
#include "Camera.h"

/**
 * @class SceneRenderer
 * @brief Renders a Scene object to produce a Color** 
 * 
 * A SceneRenderer object renders a Scene object to produce a Color**  
*/
class SceneRenderer {
    public:
        /**
         * @brief Constructor assigns scene to SceneRenderer object
         * @param scene The scene to be rendered
         * @param imageWidth The width of the rendered image
         * @param imageHeight The height of the rendered image
        */
        SceneRenderer(Scene* scene, Camera* camera, int imageWidth, int imageHeight);

        /**
         * @brief Returns image of the rendered scene
         * @return The image of the rendered scene
        */
        virtual Color** renderScene() = 0;

    protected:
        Scene* scene;
        Camera* camera;
        int imageWidth;
        int imageHeight;
        float aspectRatio;
};

#endif