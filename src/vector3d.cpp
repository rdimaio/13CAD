/**
 * @file vector3d.cpp
 * @brief Source file for the Vector3D class
 * @author Riccardo Di Maio
 * @version 1.0 08/11/18
 */

#include "vector3d.h"
#include <cmath>

Vector3D::Vector3D(){ 

    this->x=0.0;
    this->y=0.0;
    this->z=0.0;
}


Vector3D::Vector3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::~Vector3D(){}

double Vector3D::getX() {
	return this->x;
}

double Vector3D::getY() {
	return this->y;
}

double Vector3D::getZ() {
	return this->z;
}

void Vector3D::setX(double x) {
	this->x = x;
}

void Vector3D::setY(double y) {
	this->y = y;
}

void Vector3D::setZ(double z) {
	this->z = z;
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
Vector3D Vector3D::operator*(double scalar) {
    Vector3D result(this->x * scalar, this->y * scalar, this->z * scalar);
    return result;
}

/**
 * Scalar multiplication - vector on rhs
 */
Vector3D operator*(double scalar, Vector3D v) {
    Vector3D result(v.x * scalar, v.y * scalar, v.z * scalar);
    return result;
}

/**
 *  Dot product
 */
double Vector3D::dot(Vector3D rhsVector) {
    double result = this->x * rhsVector.x + this->y * rhsVector.y + this->z * rhsVector.z;
    return result;
}

/**
 *  Cross product
 */
Vector3D Vector3D::cross(Vector3D rhsVector) {
    double xResult = this->y * rhsVector.z - this->z * rhsVector.y;
    double yResult = this->z * rhsVector.x - this->x * rhsVector.z;
    double zResult = this->x * rhsVector.y - this->y * rhsVector.x;

    Vector3D result(xResult, yResult, zResult);
    return result;
}

std::ostream& operator<<(std::ostream& os, Vector3D &v) {
return os << "[" << v.x << "," << v.y << "," << v.z << "]";
}

double Vector3D::distance(Vector3D &v2) {
    // Distance between two 3D points:
    // sqrt((x2-x1)^2+(y2-y1)^2+(z2-z1)^2)
    double xDiff = v2.getX() - this->getX();
    double yDiff = v2.getY() - this->getY();
    double zDiff = v2.getZ() - this->getZ();

    double distance = sqrt(xDiff*xDiff + yDiff*yDiff + zDiff*zDiff);
    return distance;
}

Vector3D Vector3D::midpoint(Vector3D &v2) {

    double x = (this->getX() + v2.getX()) / 2;
    double y = (this->getY() + v2.getY()) / 2;
    double z = (this->getZ() + v2.getZ()) / 2;

    Vector3D vMid(x, y, z);

    return vMid;
}