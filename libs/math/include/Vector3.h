#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <algorithm>
#include <string>

/**
 * @class Vector3
 * @brief Represents an 3D vector
 * 
 * A Vector object is a representation of a 3D vector. It supports
 * all standard vector operations. 
*/
class Vector3 {
    public:
        /**
         * @brief Constructor assigns entries to the Vector3 object
         * @param x The x entry of the Vector3 object
         * @param y The y entry of the Vector3 object
         * @param z The z entry of the Vector3 object
        */
        Vector3(float x, float y, float z);

        /**
         * @brief Constructor for default Vector3 object
        */
        Vector3();

        /**
         * @brief Copy constructor for Vector3 object
         * @param copyVec The vector to be copied
        */
        Vector3(const Vector3& copyVec);
        
        /**
         * @brief Destructor for Vector3 object
        */
        ~Vector3();

        /**
         * @brief Returns the x entity of the Vector3 object
         * @return The x entity of the Vector3 object
        */
        float getX();

        /**
         * @brief Returns the y entity of the Vector3 object
         * @return The y entity of the Vector3 object
        */
        float getY();

        /**
         * @brief Returns the z entity of the Vector3 object
         * @return The z entity of the Vector3 object
        */
        float getZ();

        /**
         * @brief Returns magnitude of Vector3 object
        */
        float magnitude();

        /**
         * @brief Returns sum of entities of the Vector3 object
         * @return The sum of entities of the Vector3 object
        */
        float sum();

        /**
         * @brief Returns distance between the Vector3 object and the Vector3 otherVec
         * @param otherVec The vector to be calculated distance between
         * @return The distance between the Vector3 object and the Vector3 otherVec
        */
        float distance(Vector3 otherVec);

        /**
         * @brief Noramlizes the Vector3 object
        */
        void noramlize();

        /**
         * @brief Negates the entries in the Vector3 object
        */
        void negate();

        /**
         * @brief Negates the entries in the Vector3 object
         * @param xMax The maximum value of x to clamp
         * @param yMax The maximum value of y to clamp
         * @param zMax The maximum value of z to clamp
        */
        void clamp(float xMax, float yMax, float zMax);

        /**
         * @brief Adds the Vector3 otherVec to the Vector3 object
         * @param otherVec The vector to be added to the Vector3 object
        */
        void add(Vector3 otherVec);

        /**
         * @brief Subtracts the Vector3 otherVec to the Vector3 object
         * @param otherVec The vector to be subtracted to the Vector3 object
        */
        void subtract(Vector3 otherVec);

        /**
         * @brief Raises the entries in the Vector3 object to exponent
         * @param exponent The exponent to raise the Vector3 object to
        */
        void power(float exponent);

        /**
         * @brief Raises the entries in the Vector3 object to the second power
        */
        void square();

        /**
         * @brief Multiplies the entries in the Vector3 object by coefficient
         * @param coefficient The coefficient to multiply the Vector3 object by
        */
        void multiplyCoefficient(float coefficient);

        /**
         * @brief Returns the Vector3 object made by the dot product of the Vector3 object and the Vector3 otherVec
         * @param otherVec The vector to multiply by dot product
         * @return The Vector3 object made by the dot product of the Vector3 object and the Vector3 otherVec
        */
        float dotProduct(Vector3 otherVec);

        /**
         * @brief Returns the Vector3 object made by the cross product of the Vector3 object and the Vector3 otherVec
         * @param otherVec The vector to multiply by cross product
         * @return The Vector3 object made by the cross product of the Vector3 object and the Vector3 otherVec
        */
        Vector3 crossProduct(Vector3 otherVec);

        /**
         * @brief Returns the Vector3 object made by the product of the Vector3 object and the Vector3 otherVec
         * @param otherVec The vector to multiply by product
         * @return The Vector3 object made by the product of the Vector3 object and the Vector3 otherVec
        */
        Vector3 multiplyVector(Vector3 otherVec);

        /**
         * @brief Returns the Vector3 object made by the average of the Vector3 object and the Vector3 otherVec
         * @param otherVec The vector to average by
         * @return The Vector3 object made by the average of the Vector3 object and the Vector3 otherVec
        */
        Vector3 average(Vector3 otherVec);

        /**
         * @brief Returns the Vector3 object made by the negating the Vector3 object
         * @return The Vector3 object made by the negating the Vector3 object
        */
        Vector3 operator-();

        /**
         * @brief Returns the Vector3 object made by the sum of the Vector3 object and the Vector3 otherVec
         * @param otherVec The vector to add by
         * @return The Vector3 object made by the sum of the Vector3 object and the Vector3 otherVec
        */
        Vector3 operator+(const Vector3& otherVec);

        /**
         * @brief Returns the Vector3 object made by the difference of the Vector3 object and the Vector3 otherVec
         * @param otherVec The vector to subtract by
         * @return The Vector3 object made by the difference of the Vector3 object and the Vector3 otherVec
        */
        Vector3 operator-(const Vector3& otherVec);

        /**
         * @brief Returns the Vector3 object made by the product of the Vector3 object and coefficient
         * @param coefficient The coefficient to multiply by
         * @return The Vector3 object made by the product of the Vector3 object and coefficient
        */
        Vector3 operator*(float coefficient);

        /**
         * @brief Returns the Vector3 object made by the quotient of the Vector3 object and coefficient
         * @param divisor The divisor to divide by
         * @return The Vector3 object made by the quoient of the Vector3 object and divisor
        */
        Vector3 operator/(float divisor);

        /**
         * @brief Returns if the Vector3 object and the Vector3 object are equal within delta
         * @param otherVec The vector to compare
         * @param delta The delta that entries can be contained within for equality 
         * @return The boolean value for if the Vector3 object and the Vector3 object are equal within delta
        */
        bool equals(Vector3 otherVec, float delta);

        /**
         * @brief Returns if the Vector3 object and the Vector3 object are equal within a delta
         * @param otherVec The vector to compare
         * @return The boolean value for if the Vector3 object and the Vector3 object are equal within a delta
        */
        bool equals(Vector3 otherVec);

        /**
         * @brief Returns the std::string representation of the Vector3 object
         * @return The std::string representation of the Vector3 object
        */
        std::string toString();

    private:
        float x;
        float y;
        float z;
};

#endif