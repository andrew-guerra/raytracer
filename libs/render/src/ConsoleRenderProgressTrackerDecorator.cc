#include "../include/ConsoleRenderProgressTrackerDecorator.h"

ConsoleRenderProgressTrackerDecorator::ConsoleRenderProgressTrackerDecorator(SceneRenderer* renderer) {
    this->renderer = renderer;
}

void ConsoleRenderProgressTrackerDecorator::displayRenderMetrics() {
    std::cout << "Rendering " << this->imageWidth << "x" << this->imageHeight << " image" << std::endl;
}

void ConsoleRenderProgressTrackerDecorator::displayProgress() {
    std::cout << this->getPercentageSceneRendered() * 100 << "%" << "\r";
}

Color** ConsoleRenderProgressTrackerDecorator::renderScene() {
    Color** renderedImage = RenderProgressTrackerDecorator::renderScene();
    
    // account for newline after carriage return
    std::cout << std::endl;

    return renderedImage;
}