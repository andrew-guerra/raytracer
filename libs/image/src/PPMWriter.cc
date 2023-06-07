#include "../include/PPMWriter.h"

PPMWriter::PPMWriter(int maxColorValue, std::string fileName, int imageWidth, int imageHeight) : ImageFileWriter(fileName, imageWidth, imageHeight) {
    this->maxColorValue = maxColorValue;
}

PPMWriter::~PPMWriter() {
    
}

void PPMWriter::writeImage(Color** pixelColors) {
    writeHeader();
    writeBody(pixelColors);
}

void PPMWriter::writeHeader() {
    this->imageFile << "P3 " << this->imageWidth << " " << this->imageHeight << " " << this->maxColorValue << std::endl;
}

void PPMWriter::writeBody(Color** pixelColors) {
    for(int row = 0; row < this->imageHeight; row++) {
		for(int col = 0; col < this->imageWidth; col++) {
			this->imageFile << round(pixelColors[row][col].getRed() * this->maxColorValue) << " ";
			this->imageFile << round(pixelColors[row][col].getGreen() * this->maxColorValue) << " ";
			this->imageFile << round(pixelColors[row][col].getBlue() * this->maxColorValue);
			
			this->imageFile << std::endl;
		}
	}

}