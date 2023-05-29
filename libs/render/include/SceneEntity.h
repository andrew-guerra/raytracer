#ifndef SCENE_ENTITY_H
#define SCENE_ENTITY_H

#include "../../math/include/Vector3.h"
#include "../../math/include/Ray.h"
#include "Color.h"

/**
 * @class SceneEntity
 * @brief Represents an entity inside a rendered scene
 * 
 * A SceneEntity object will be an object inside a rendered scene. A SceneEntity object
 * can be a primitive like a triangle or quads, but can also be a collection of primitives
 * like a model, or defined by an equation such as a sphere.
*/
class SceneEntity {
    public:
        /**
         * @brief Constructor assigns position to SceneEntity object
         * @param position The position of the SceneEntity object
        */
        SceneEntity(Vector3* position);

        /**
         * @brief Constructor for SceneEntity object
        */
        SceneEntity();

        /**
         * @brief Destructor for SceneEntity object
        */
        ~SceneEntity();

        /**
         * @brief Gets position of SceneEntity object
         * @return position of SceneEntity object
        */
        virtual Vector3* getPosition();

        /**
         * @brief Sets position of SceneEntity object to position
         * @param position The position of the SceneEntity object
        */
        virtual void setPosition(Vector3* position);

        /**
         * @brief Returns the distance along ray for intersection with the SceneEntity object
         * @param ray The ray to test for an intersection with the SceneEntity object
         * @returns The distance along ray for intersection with the SceneEntity object
        */
        virtual float intersectionDistance(Ray* ray) = 0;

        /**
         * @brief Returns Color object at point on SceneEntity object
         * @param intersectionPoint The point to get color from on the SceneEntity object
         * @returns Color object at point on SceneEntity object
         * 
         * The Vector3 intersectionPoint is assumed to be on the surface of the SceneEntity object. 
         * Behavior is undefined for points that are not on the surface. 
        */
        virtual const Color* getPointColor(Vector3* intersectionPoint) = 0;

        private:
            Vector3* position;
};

#endif