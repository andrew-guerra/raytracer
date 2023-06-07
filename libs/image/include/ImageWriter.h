#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include "../../render/include/Color.h"

/**
 * @class ImageWriter
 * @brief Writes in an image
 * 
 * An ImageWriter object writers in an image. 
*/
class ImageWriter {
    public:
        /**
         * @brief Constructor for the ImageWriter object
        */
        ImageWriter(int imageWidth, int imageHeight);

        /**
         * @brief Destuctor for the ImageWriter object
        */
        ~ImageWriter();

        /**
         * @brief Writes out with colors for each pixel
         * @param pixelColors The colors for pixels in the image
        */
        virtual void writeImage(Color** pixelColors) = 0;

    protected:
        int imageWidth;
        int imageHeight;
};

#endif