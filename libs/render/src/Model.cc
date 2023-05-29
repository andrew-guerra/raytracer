#include "../include/Model.h"
#include "../include/Primitive.h"

Model::Model(Primitive* primitives) : SceneEntity() {
    this->primitives = primitives;
}