#include "../include/RenderProgressTrackerDecorator.h"

RenderProgressTrackerDecorator::RenderProgressTrackerDecorator(SceneRenderer* renderer) {
    this->renderer = renderer;
}

RenderProgressTrackerDecorator::RenderProgressTrackerDecorator() {
    this->renderer = nullptr;
}

Color** RenderProgressTrackerDecorator::renderScene() {
    this->displayRenderMetrics();

    Color** renderedImage = this->renderer->renderScene();
    
    this->displayProgress();

    return renderedImage;
}