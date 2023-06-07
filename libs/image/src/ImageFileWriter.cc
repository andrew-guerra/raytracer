#include "../include/ImageFileWriter.h"

ImageFileWriter::ImageFileWriter(std::string fileName, int imageWidth, int imageHeight) : ImageWriter(imageWidth, imageHeight) {
    this->imageFile.open(fileName);
}

ImageFileWriter::~ImageFileWriter() {
    this->imageFile.close();
}