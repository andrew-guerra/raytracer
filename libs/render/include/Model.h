#ifndef MODEL_H
#define MODEL_H

#include "SceneEntity.h"
#include "Primitive.h"

/**
 * @class Model
 * @brief Represents an model in a rendered scene
 * 
 * A Model object is a representation of the model made up of primitives. It 
 * stores all of the primitives. It has all of 
 * the properties of a SceneEntity object.
*/
class Model : public SceneEntity {
    public:
        /**
         * @brief Constructor assigns primitives to Model object
         * @param primitives The primitives that make up the Model object
        */
        Model(Primitive* primitives);

    private:
        Primitive* primitives;
};

#endif