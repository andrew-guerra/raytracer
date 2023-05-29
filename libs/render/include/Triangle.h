#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "SceneEntity.h"
#include "Primitive.h"

/**
 * @class Triangle
 * @brief Represents an triangle primitive in a rendered scene
 * 
 * A Triangle object is a representation of the triangle primitive. It is defined 
 * by three points in global coordinates. It has all of the properties of a SceneEntity object.
*/
class Triangle : public Primitive {
    public:
        /**
         * @brief Constructor assigns points to Triangle object
         * @param points The points defining the Triangle object
        */
        Triangle(Vector3* points);
};

#endif