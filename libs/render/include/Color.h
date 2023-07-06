#ifndef COLOR_H
#define COLOR_H

#include <string>

/**
 * @class Color
 * @brief Represents an RGB color
 * 
 * A Color object represents an RGB color on a floating point scale from 0-1.
*/
class Color {
    public:
        /**
         * @brief Constructor assigns color components to Color object
         * @param r The red component of the color
         * @param g The green component of the color
         * @param b The blue component of the color
        */
        Color(double r, double g, double b);

        /**
         * @brief Copy constructor for Color object
         * @param otherColor The color to copy
        */
        Color(const Color& otherColor);

        /**
         * @brief Gets the red compoenet of the Color object
        */
        double getRed();

        /**
         * @brief Gets the green compoenet of the Color object
        */
        double getGreen();

        /**
         * @brief Gets the blue compoenet of the Color object
        */
        double getBlue();

        /**
         * @brief Returns the Color object made by the sum of the Color object and otherColor
         * @param otherColor The color to add by
         * @return The Color object made by the sum of the Color object and otherColor
        */
        Color operator+(Color otherColor);

        /**
         * @brief Returns the Color object made by the sum of the Color object and otherColor
         * @param otherColor The color to add by
         * @return The Color object made by the sum of the Color object and otherColor
        */
        Color operator+=(Color otherColor);

        /**
         * @brief Returns the Color object made by the product of the Color object and coefficient
         * @param coefficent The coefficent to multiply by
         * @return The Color object made by the product of the Color object and coefficient
        */
        Color operator*(float coefficent);

        /**
         * @brief Returns the Color object made by the product of the Color object and coefficient
         * @param coefficent The coefficent to multiply by
         * @return The Color object made by the product of the Color object and coefficient
        */
        Color multipyCoefficent(float coefficent);

        std::string toString();

    private:
        double r;
        double g;
        double b;

        float clampColorChannel(float num);
        float clamp(float num, float min, float max);
};

extern Color RED;
extern Color GREEN;
extern Color BLUE;
extern Color WHITE;
extern Color BLACK;

#endif