#ifndef SCENE_H
#define SCENE_H

#include "SceneEntity.h"

/**
 * @class Scene
 * @brief Represents an scene to be rendered
 * 
 * A Scene object is a representation of a collection of SceneEntities.
 * It stores the SceneEntities as well as information including default background color.
*/
class Scene {
    /**
     * @brief Constructor assigns position to Scene object
     * @param position The entities of the Scene object
    */
    Scene(SceneEntity* entities);

    /**
     * @brief Constructor for Scene object
    */
    Scene();

    /**
     * @brief Destructor for Scene object
    */
    ~Scene();

    private:
        SceneEntity* entities;
};

#endif