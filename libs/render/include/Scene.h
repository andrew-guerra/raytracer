#ifndef SCENE_H
#define SCENE_H

#include "SceneEntity.h"
#include <vector>

/**
 * @class Scene
 * @brief Represents an scene to be rendered
 * 
 * A Scene object is a representation of a collection of SceneEntities.
 * It stores the SceneEntities as well as information including default background color.
*/
class Scene {
    public:
        /**
         * @brief Constructor assigns position to Scene object
         * @param entities The entities of the Scene object
         * @param backgroundColor The color of the background of the scene
        */
        Scene(std::vector<SceneEntity*>& entities, const Color* backgroundColor);

        /**
         * @brief Constructor for Scene object
        */
        Scene();

        /**
         * @brief Destructor for Scene object
        */
        ~Scene();

        /**
         * @brief Returns the entities in the Scene object
         * @return The entities in the Scene object
        */
        std::vector<SceneEntity*> getEntities();

        /**
         * @brief Returns the number of entities in the Scene object
         * @return The number of entities in the Scene object
        */
        int getNumEntities();

        /**
         * @brief Returns the background color for the Scene object
         * @return The background color for the Scene object
        */
        const Color* getBackgroundColor();

    private:
        std::vector<SceneEntity*> entities;
        const Color* backgroundColor;
};

#endif