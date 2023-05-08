
#ifndef PPMGENERATOR_H
#define PPMGENERATOR_H

#include <string>
#include "graphicsTools.h"

sceneSpecs_t getSceneSpecifications(int argc, char** argv, std::string& filename);
void writePPMFile(std::string filename, color_t** pixels, int width, int height);

#endif