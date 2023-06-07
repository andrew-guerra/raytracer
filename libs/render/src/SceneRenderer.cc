#include "../include/SceneRenderer.h"

SceneRenderer::SceneRenderer(Scene* scene, Camera* camera, int imageWidth, int imageHeight) {
    this->scene = scene;
    this->camera = camera;
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    this->aspectRatio = (imageWidth * 1.0) / (imageHeight * 1.0);
}