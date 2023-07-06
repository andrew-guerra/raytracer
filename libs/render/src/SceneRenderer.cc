#include "../include/SceneRenderer.h"

SceneRenderer::SceneRenderer(Scene* scene, Camera* camera, int imageWidth, int imageHeight) {
    this->scene = scene;
    this->camera = camera;
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    this->aspectRatio = (imageWidth * 1.0) / (imageHeight * 1.0);
}

SceneRenderer::SceneRenderer() {
    this->scene = new Scene();
    this->camera = new Camera();
    this->imageWidth = 100;
    this->imageHeight = 100;
    this->aspectRatio = 1;
}