#include "vector.h"

Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::~Vector3D() {
    
}

Vector3D Vector3D::operator+(Vector3D rhsVector) {
    Vector3D result(this->x + rhsVector.x, this->y + rhsVector.y, this->z + rhsVector.z);
    return result;
}

Vector3D Vector3D::operator-(Vector3D rhsVector) {
    Vector3D result(this->x - rhsVector.x, this->y - rhsVector.y, this->z - rhsVector.z);
    return result;
}

bool operator==(const Vector3D& lhsVector, const Vector3D& rhsVector) {
        if (lhsVector.x == rhsVector.x && lhsVector.y == rhsVector.y && lhsVector.z == rhsVector.z) {
        return true;
    } else {
        return false;
    }
}


/**
 * Scalar multiplication - vector on lhs
 */
Vector3D Vector3D::operator*(float scalar) {
    Vector3D result(this->x * scalar, this->y * scalar, this->z * scalar);
    return result;
}

/**
 * Scalar multiplication - vector on rhs
 */
Vector3D operator*(float scalar, Vector3D v) {
    Vector3D result(v.x * scalar, v.y * scalar, v.z * scalar);
    return result;
}

/**
 *  Dot product
 */
float Vector3D::dot(Vector3D rhsVector) {
    float result = this->x * rhsVector.x + this->y * rhsVector.y + this->z * rhsVector.z;
    return result;
}

/**
 *  Cross product
 */
Vector3D Vector3D::cross(Vector3D rhsVector) {
    float xResult = this->y * rhsVector.z - this->z * rhsVector.y;
    float yResult = this->z * rhsVector.x - this->x * rhsVector.z;
    float zResult = this->x * rhsVector.y - this->y * rhsVector.x;

    Vector3D result(xResult, yResult, zResult);
    return result;
}

std::ostream& operator<<(std::ostream& os, Vector3D &v) {
return os << "[" << v.x << "," << v.y << "," << v.z << "]";
}