#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

/**
 * @class Ray
 * @brief Represents an 3D ray
 * 
 * A Ray object is a representation of a 3D ray. It is defined
 * by a origin vector and a direction vector. It supports
 * all standard ray operations.
*/
class Ray {
    public:
        /**
         * @brief Constructor assigns origin and direction to the Ray object
         * @param origin The origin vector of the Ray object
         * @param direction The direction vector of the Ray object
        */
        Ray(Vector3* origin, Vector3* direction);

        /**
         * @brief Constructor for default Ray object
        */
        Ray();

        /**
         * @brief Copy constructor for Ray object
         * @param copyRay The ray to be copied
        */
        Ray(const Ray& copyRay);

        /**
         * @brief Destructor for Ray object
        */
        ~Ray();

        /**
         * @brief Returns origin vector of the Ray object
         * @return The origin vector of the Ray object
        */
        Vector3* getOrigin();

        /**
         * @brief Returns direction vector of the Ray object
         * @return The direction vector of the Ray object
        */
        Vector3* getDirection();

        /**
         * @brief Returns point along the Ray object's direction and origin based on scaler
         * @param scaler The scaler for the direction vector
         * @return The point along the Ray object's direction and origin based on scaler
        */
        Vector3 getMemberPoint(float scaler);

        /**
         * @brief Scales the Ray object's direction vector by scaler
         * @param scaler The scaler for the direction vector 
        */
        void scale(float scaler);

        /**
         * @brief Rotates the Ray object's direction vector by xTheta, yTheta, and zTheta
         * @param xTheta The rotation for the direction vector around the X axis
         * @param yTheta The rotation for the direction vector around the Y axis 
         * @param zTheta The rotation for the direction vector around the Z axis 
        */
        void rotate(float xTheta, float yTheta, float zTheta);

        /**
         * @brief Translates the Ray object's origin vector by translationVec
         * @param translationVec The translation vector for the translation
        */
        void translate(Vector3 translationVec);

    private:
        Vector3* origin;
        Vector3* direction;
};

#endif