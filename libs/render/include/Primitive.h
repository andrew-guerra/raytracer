#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "SceneEntity.h"

/**
 * @class Primitive
 * @brief Represents an graphics primitive in a rendered scene
 * 
 * A Primitive object is a representation of a graphics primitive. It is
 * defined based on a list of points. With each point being connected to the 
 * next and previous points in the list of points. The first and last points 
 * will also be connected as the list was circular.
*/
class Primitive : public SceneEntity {
    public:
        /**
         * @brief Constructor assigns points to Primitive object
         * @param points The points defining the Primitive object
        */
        Primitive(Vector3* points);

    protected:
        Vector3* points;
};

#endif