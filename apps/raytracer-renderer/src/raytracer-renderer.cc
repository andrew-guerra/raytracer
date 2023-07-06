#include "Sphere.h"
#include "RaytracerRenderer.h"
#include "MaterialDecorator.h"
#include "LightDecorator.h"
#include "ConsoleRenderProgressTrackerDecorator.h"
#include "PPMWriter.h"
#include <iostream>

int main(int argc, char** argv) {
    Vector3* sphereLeft = new Vector3(-2, 0, -5);
    Vector3* sphereRight = new Vector3(2, 0, -5);
    Vector3* sphereCenter = new Vector3(0, 0, -5);
    Vector3* lightPos = new Vector3(0, 5, 0);
    Ray* ray = new Ray();

    //std::vector<SceneEntity*> entities{new Sphere(sphereCenter, 1)};
    std::vector<SceneEntity*> entities{new MaterialDecorator(new Sphere(sphereLeft, 1), 0.2, 0.4, .4, 20), new MaterialDecorator(new Sphere(sphereRight, 1), 0.2, 0.6, 0.6, 20)};
    std::vector<SceneEntity*> lights{new LightDecorator(new Sphere(lightPos, 1))};

    Scene* scene = new Scene(entities, lights, &BLACK);

    SceneRenderer* renderer = new RaytracerRenderer(scene, &DEFAULT_CAMERA, 600, 300, 5);
    renderer = new ConsoleRenderProgressTrackerDecorator(renderer);

    Color** image = renderer->renderScene();

    PPMWriter* imageWriter = new PPMWriter(255, "test.ppm", 600, 300);
    imageWriter->writeImage(image);

    return 0;
}
