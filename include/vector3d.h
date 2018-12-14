#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <iostream>

/**
 * 3D vector representation of a vertex.
 */
class Vector3D {
    friend class Matrix3x3;
    
    protected:
        // Spatial coordinates
        double x;
        double y;
        double z;
    
    public:
        Vector3D();
        Vector3D(double x, double y, double z);
        ~Vector3D();

		// Accessors
		double getX();
		double getY();
		double getZ();
		
		// Mutators
		void setX(double x);
		void setY(double y);
		void setZ(double z);

        // Operator overloading
        // Note: rhs stands for right hand side
        Vector3D operator+(Vector3D rhsVector);
        Vector3D operator-(Vector3D rhsVector);
        friend bool operator==(const Vector3D& lhsVector, const Vector3D& rhsVector);
        double dot(Vector3D rhsVector); // Dot product
        Vector3D cross(Vector3D rhsVector); // Cross product
        friend std::ostream& operator<<(std::ostream& os, Vector3D &v); // cout
        // Scalar multiplication
        Vector3D operator*(double scalar); // Vector on lhs
        friend Vector3D operator*(double scalar, Vector3D v); // Vector on rhs

        // Functions
        double distance(Vector3D &v2); // Distance from vertex
};

#endif /* VECTOR_H */