#ifndef COLOR_H
#define COLOR_H

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

    private:
        double r;
        double g;
        double b;
};

#endif