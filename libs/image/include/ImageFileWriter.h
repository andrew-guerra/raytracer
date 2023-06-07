#ifndef IMAGE_FILE_WRITER_H
#define IMAGE_FILE_WRITER_H

#include "ImageWriter.h"
#include <string>
#include <fstream>

/**
 * @class ImageFileWriter
 * @brief Writes in an image to a file
 * 
 * An ImageFileWriter object writes in an image to a file.
*/
class ImageFileWriter : public ImageWriter {
    public:
        /**
         * @brief Constructor for the ImageFileWriter object
         * @param fileName The file name for the image to be written to
        */
        ImageFileWriter(std::string fileName, int imageWidth, int imageHeight);

        /**
         * @brief Destructor for the ImageFileWriter object
        */
        ~ImageFileWriter();

    protected:
        std::ofstream imageFile;
};

#endif