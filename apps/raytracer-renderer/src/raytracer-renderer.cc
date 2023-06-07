//#include "Sphere.h"
//#include "RaytracerRenderer.h"
//#include "PPMWriter.h"
//#include "Vector3.h"
//#include "Camera.h"
#include "Sphere.h"
//#include "Scene.h"
//#include "Color.h"
//#include "Ray.h"
#include "RaytracerRenderer.h"
#include "LightDecorator.h"
#include "PPMWriter.h"
#include <iostream>

int main(int argc, char** argv) {
    Vector3* sphereLeft = new Vector3(-1, 0, -5);
    Vector3* sphereRight = new Vector3(1, 0, -5);
    Vector3* lightPos = new Vector3(0, 3, -5);
    Ray* ray = new Ray();

    std::vector<SceneEntity*> entities{new Sphere(sphereLeft, 1), new Sphere(sphereRight, 1), new LightDecorator(new Sphere(lightPos, 1))};

    Camera* camera = new Camera(new Ray(new Vector3(0, 0, 0), new Vector3(0, 0, -1)), new Vector3(0, 1, 0), 90, 90);
    Scene* scene = new Scene(entities, &WHITE);
    RaytracerRenderer* renderer = new RaytracerRenderer(scene, camera, 300, 300, 5);

    Color** image = renderer->renderScene();

    PPMWriter* imageWriter = new PPMWriter(255, "test.ppm", 300, 300);
    imageWriter->writeImage(image);

    return 0;
}
