#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H

#include "SceneRenderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Color.h"

#define PI 3.14159265

/**
 * @class RaytracerRenderer
 * @brief Renders a Scene object to produce a Color** using the ray tracing method
 * 
 * A RaytracerRenderer object Renders a Scene object to produce a Color** using the ray tracing method.
 * Rays from the camera (backwards ray tracing) and traverse through the scene as if it were a light ray.
 * The ray will then return color information based on intersections or lack thereof.  
*/
class RaytracerRenderer : public SceneRenderer {
    public:
        /**
         * @brief Constructor assigns scene to SceneRenderer object
         * @param scene Scene to be rendered
        */
        RaytracerRenderer(Scene* scene, Camera* camera, int imageWidth, int imageHeight, float viewDistance);

        virtual Color** renderScene();

    private:
        Ray** rays;
        float viewWindowWidth;
        float viewWindowHeight;
        float viewDistance;

        Ray** generateRays();
        Color** generatePixelColors();
        const Color* traceRay(Ray ray);
        float getShadowFlag(Ray ray);
        SceneEntity* getClosestEntity(Ray ray);

        float toRadians(float degrees);

        const float EPLSION = 0.01;
};

#endif