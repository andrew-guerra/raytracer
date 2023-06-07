#ifndef PPM_WRITER_H
#define PPM_WRITER_H

#include "ImageFileWriter.h"
#include <string>
#include <cmath>

/**
 * @class PPMWriter
 * @brief Writes in an image to a PPM file
 * 
 * An PPMWriter object writes in an image to a PPM file.
*/
class PPMWriter : public ImageFileWriter {
    public:
        /**
         * @brief Constructor for the PPMWriter object
         * @param fileName The file name for the image to be written to
        */
        PPMWriter(int maxColorValue, std::string fileName, int imageWidth, int imageHeight);
        
        /**
         * @brief Destructor for the PPMWriter object
        */
        ~PPMWriter();

        virtual void writeImage(Color** pixelColors);

    private:
        int maxColorValue;

        void writeHeader();

        void writeBody(Color** pixelColors);
};

#endif