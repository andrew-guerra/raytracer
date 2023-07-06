#include "../include/SceneRendererBaseDecorator.h"

SceneRendererBaseDecorator::SceneRendererBaseDecorator(SceneRenderer* renderer) {
    this->renderer = renderer;
}

SceneRendererBaseDecorator::SceneRendererBaseDecorator() {
    this->renderer = nullptr;
}

Color** SceneRendererBaseDecorator::renderScene() {
    return this->renderer->renderScene();
}

float SceneRendererBaseDecorator::getPercentageSceneRendered() {
    return this->renderer->getPercentageSceneRendered();
}