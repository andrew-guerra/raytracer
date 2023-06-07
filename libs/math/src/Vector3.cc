#include "../include/Vector3.h"

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(const Vector3& copyVec) {
    this->x = copyVec.x;
    this->y = copyVec.y;
    this->z = copyVec.z;
}

Vector3::~Vector3() {

}

float Vector3::getX() {
    return this->x;
}

float Vector3::getY() {
    return this->y;
}

float Vector3::getZ() {
    return this->z;
}

float Vector3::magnitude() {
    return std::sqrt(this->dotProduct(*this));
}

float Vector3::sum() {
    return this->x + this->y + this->z;
}

float Vector3::distance(Vector3 otherVec) {
    return (*this - otherVec).magnitude();
}

void Vector3::noramlize() {
    float magnitude = this->magnitude();

    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

void Vector3::negate() {
    this->multiplyCoefficient(-1.0);
}

void Vector3::clamp(float xMax, float yMax, float zMax) {
    this->x = std::min(this->x, xMax);
    this->y = std::min(this->y, yMax);
    this->z = std::min(this->z, zMax);
}

void Vector3::add(Vector3 otherVec) {
    this->x += otherVec.x;
    this->y += otherVec.y;
    this->z += otherVec.z;
}

void Vector3::subtract(Vector3 otherVec) {
    this->x -= otherVec.x;
    this->y -= otherVec.y;
    this->z -= otherVec.z;
}

void Vector3::power(float exponent) {
    this->x = std::pow(this->x, exponent);
    this->y = std::pow(this->y, exponent);
    this->z = std::pow(this->z, exponent);
}

void Vector3::square() {
    this->x *= this->x;
    this->y *= this->y;
    this->z *= this->z;
}

void Vector3::multiplyCoefficient(float coefficient) {
    this->x *= coefficient;
    this->y *= coefficient;
    this->z *= coefficient;
}

float Vector3::dotProduct(Vector3 otherVec) {
    return this->x * otherVec.x + this->y * otherVec.y + this->z * otherVec.z;
}

Vector3 Vector3::crossProduct(Vector3 otherVec) {
    float xNew = this->y * otherVec.z - this->z * otherVec.y;
    float yNew = this->z * otherVec.x - this->x * otherVec.z;
    float zNew = this->x * otherVec.y - this->y * otherVec.x;

    return Vector3(xNew, yNew, zNew);
}

Vector3 Vector3::multiplyVector(Vector3 otherVec) {
    float xNew = this->x * otherVec.x;
    float yNew = this->y * otherVec.y;
    float zNew = this->z * otherVec.z;

    return Vector3(xNew, yNew, zNew);
}

Vector3 Vector3::average(Vector3 otherVec) {
    float xNew = (this->x + otherVec.x) / 2.0;
    float yNew = (this->y + otherVec.y) / 2.0;
    float zNew = (this->z + otherVec.z) / 2.0;

    return Vector3(xNew, yNew, zNew);
}

Vector3 Vector3::operator-() {
    float xNew = -this->x;
    float yNew = -this->y;
    float zNew = -this->z;

    return Vector3(xNew, yNew, zNew);
}

Vector3 Vector3::operator+(const Vector3& otherVec) {
    float xNew = this->x + otherVec.x;
    float yNew = this->y + otherVec.y;
    float zNew = this->z + otherVec.z;

    return Vector3(xNew, yNew, zNew);
}

Vector3 Vector3::operator-(const Vector3& otherVec) {
    float xNew = this->x - otherVec.x;
    float yNew = this->y - otherVec.y;
    float zNew = this->z - otherVec.z;

    return Vector3(xNew, yNew, zNew);
}

Vector3 Vector3::operator*(float coefficient) {
    float xNew = this->x * coefficient;
    float yNew = this->y * coefficient;
    float zNew = this->z * coefficient;

    return Vector3(xNew, yNew, zNew);
}

Vector3 Vector3::operator/(float divisor) {
    float xNew = this->x / divisor;
    float yNew = this->y / divisor;
    float zNew = this->z / divisor;

    return Vector3(xNew, yNew, zNew);
}

bool Vector3::equals(Vector3 otherVec, float delta) {
    return std::abs(this->x - otherVec.x) <= delta &&
           std::abs(this->y - otherVec.y) <= delta &&
           std::abs(this->z - otherVec.z) <= delta;
                                                 
}

bool Vector3::equals(Vector3 otherVec) {
    return this->equals(otherVec, 0.01);
}

std::string Vector3::toString() {
    return "[" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + "]";
}