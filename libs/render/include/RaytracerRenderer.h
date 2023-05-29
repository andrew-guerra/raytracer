#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H

#include "SceneRenderer.h"

/**
 * @class RaytracerRenderer
 * @brief Renders a Scene object to produce a Color** using the ray tracing method
 * 
 * A RaytracerRenderer object Renders a Scene object to produce a Color** using the ray tracing method.
 * Rays from the camera (backwards ray tracing) and traverse through the scene as if it were a light ray.
 * The ray will then return color information based on intersections or lack thereof.  
*/
class RaytracerRenderer : public SceneRenderer {

};

#endif