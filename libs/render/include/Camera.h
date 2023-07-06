#ifndef CAMERA_H
#define CAMERA_H

#include "../../math/include/Ray.h"

/**
 * @class Camera
 * @brief Represents an camera to be rendered
 * 
 * A Camera object is a representation of a camera in a scene.
 * It stores the ray of the camera (origin and direction) and the up direction vector.
*/
class Camera {
    public:
        /**
         * @brief Constructor assigns the camera ray and up direction vector to Camera object
         * @param cameraRay The camera ray of the Camera object
         * @param upVector The up vector of the Camera object
        */
        Camera(Ray* cameraRay, Vector3* upVector, float hfov, float vfov);

        /**
         * @brief Constructor for Scene object
        */
        Camera();

        /**
         * @brief Destructor for Scene object
        */
        ~Camera();

        /**
         * @brief Returns the camera ray (origin and direction) of the Camera object
         * @return The camera ray (origin and direction) of the Camera object
        */
        Ray* getCameraRay();

        /**
         * @brief Returns the up vector of the Camera object
         * @return The up vector of the Camera object
        */
        Vector3* getUpVector();

        /**
         * @brief Returns the horizontal field of view of the Camera object
         * @return The vertical field of view of the Camera object
        */
        float getHorizontalFOV();

        /**
         * @brief Returns the horizontal field of view of the Camera object
         * @return The vertical field of view of the Camera object
        */
        float getVerticalFOV();

    private:
        Ray* cameraRay;
        Vector3* upVector;
        float hfov;
        float vfov;
};

extern Camera DEFAULT_CAMERA;

#endif