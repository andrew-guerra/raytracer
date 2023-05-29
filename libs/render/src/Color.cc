#include "../include/Color.h"

Color::Color(double r, double g, double b) {
    this->r = r;
    this->g = g;
    this->b = b;
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