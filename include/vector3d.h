/**
 * @file vector3d.h
 * @brief Header file for the Vector3D class
 * @author Riccardo Di Maio
 * @version 1.0 08/11/18
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <iostream>

/**
 * 3D vector representation of a vertex.
 */
class Vector3D
{
    friend class Matrix3x3;

  protected:
    // Spatial coordinates

    /**
    * X coordinate
    */
    double x;

    /**
    * Y coordinate
    */
    double y;

    /**
    * Z coordinate
    */
    double z;

  public:
    Vector3D();
    Vector3D(double x, double y, double z);
    ~Vector3D();

    // Accessors

    /**
    * Return X coordinate
    */
    double getX();

    /**
    * Return Y coordinate
    */
    double getY();

    /**
    * Return Z coordinate
    */
    double getZ();

    // Mutators

    /**
    * Set X coordinate
    */
    void setX(double x);

    /**
    * Set Y coordinate
    */
    void setY(double y);

    /**
    * Set Z coordinate
    */
    void setZ(double z);

    // Operator overloading
    // Note: rhs stands for right hand side

    /**
    * Addition operation
    */
    Vector3D operator+(Vector3D rhsVector);

    /**
    * Subtract operation
    */
    Vector3D operator-(Vector3D rhsVector);

    /**
    * Equality operation
    */
    friend bool operator==(const Vector3D &lhsVector, const Vector3D &rhsVector);

    /**
    * Dot product (returns a single value)
    */
    double dot(Vector3D rhsVector);

    /**
    * Cross product (returns a Vector3D)
    */
    Vector3D cross(Vector3D rhsVector);

    /**
    * Scalar multiplication (Vector3D on left hand side)
    */
    Vector3D operator*(double scalar);

    /**
    * Scalar multiplication (Vector3D on right hand side)
    */
    friend Vector3D operator*(double scalar, Vector3D v);

    /**
    * Output Vector3D
    */
    friend std::ostream &operator<<(std::ostream &os, Vector3D &v); // cout

    // Misc functions

    /**
    * Return distance between two vertices
    */
    double distance(Vector3D &v2);

    /**
    * Return midpoint between two vertices
    */
    Vector3D midpoint(Vector3D &v2);
};

#endif /* VECTOR_H */