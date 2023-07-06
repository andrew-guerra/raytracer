#include "../include/Color.h"

Color::Color(double r, double g, double b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(const Color& otherColor) {
    this->r = otherColor.r;
    this->g = otherColor.g;
    this->b = otherColor.b;
}

double Color::getRed() {
    return this->r;
}

double Color::getGreen() {
    return this->g;
}

double Color::getBlue() {
    return this->b;
}

Color Color::operator+(Color otherColor) {
    float rNew = clampColorChannel(this->r + otherColor.r);
    float bNew = clampColorChannel(this->g + otherColor.g);
    float gNew = clampColorChannel(this->b + otherColor.b);

    return Color(rNew, bNew, gNew);
}

Color Color::operator+=(Color otherColor) {
    this->r = clampColorChannel(this->r + otherColor.r);
    this->g = clampColorChannel(this->g + otherColor.g);
    this->b = clampColorChannel(this->b + otherColor.b);

    return *this;
}

Color Color::operator*(float coefficent) {
    float rNew = clampColorChannel(this->r * coefficent);
    float bNew = clampColorChannel(this->g * coefficent);
    float gNew = clampColorChannel(this->b * coefficent);

    return Color(rNew, bNew, gNew);
}

Color Color::multipyCoefficent(float coefficent) {
    float rNew = clampColorChannel(this->r * coefficent);
    float bNew = clampColorChannel(this->g * coefficent);
    float gNew = clampColorChannel(this->b * coefficent);

    return Color(rNew, bNew, gNew);
}

float Color::clampColorChannel(float num) {
    return clamp(num, 0, 1);
}

float Color::clamp(float num, float min, float max) {
    if(num > max) {
        return max;
    }

    if(num < min) {
        return min;
    }

    return num;
}

std::string Color::toString() {
    return "[" + std::to_string(this->r) + "," + std::to_string(this->g) + "," + std::to_string(this->b) + "]";
}

Color RED = Color(1.0f, 0.0f, 0.0f);
Color GREEN = Color(0.0f, 1.0f, 0.0f);
Color BLUE = Color(0.0f, 0.0f, 1.0f);
Color WHITE = Color(1.0f, 1.0f, 1.0f);
Color BLACK = Color(0.0f, 0.0f, 0.0f);