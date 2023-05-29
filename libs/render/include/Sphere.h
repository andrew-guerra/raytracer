#ifndef SPHERE_H
#define SPHERE_H

#include "SceneEntity.h"

/**
 * @class Sphere
 * @brief Represents an sphere in a rendered scene
 * 
 * A Sphere object is a representation of a sphere defined by an intersection equation. 
 * It is defined by the position of its center in global coordinates and its radius.
 * It has all of the properties of a SceneEntity object.
*/
class Sphere : public SceneEntity {
    public:
        /**
         * @brief Constructor assigns center position and radius to Sphere object
         * @param center The center position of the Sphere object
         * @param radius The radius of the Sphere object
        */
        Sphere(Vector3* center, double radius);

        virtual float intersectionDistance(Ray* ray);

        virtual const Color* getPointColor(Vector3* intersectionPoint);
        
    private:
        double radius;
};

#endif