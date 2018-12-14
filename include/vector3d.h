#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <iostream>

/**
 * 3D vector representation of a vertex.
 */
class Vector3D {
    private:
        // Spatial coordinates
        float x;
        float y;
        float z;
    
    public:
        Vector3D(float x, float y, float z);
        ~Vector3D();

		// Accessors
		float getX();
		float getY();
		float getZ();
		
		// Mutators
		void setX(float x);
		void setY(float y);
		void setZ(float z);

        // Operator overloading
        // Note: rhs stands for right hand side
        Vector3D operator+(Vector3D rhsVector);
        Vector3D operator-(Vector3D rhsVector);
        friend bool operator==(const Vector3D& lhsVector, const Vector3D& rhsVector);
        float dot(Vector3D rhsVector); // Dot product
        Vector3D cross(Vector3D rhsVector); // Cross product
        friend std::ostream& operator<<(std::ostream& os, Vector3D &v); // cout
        // Scalar multiplication
        Vector3D operator*(float scalar); // Vector on lhs
        friend Vector3D operator*(float scalar, Vector3D v); // Vector on rhs

        // Functions
        double distance(Vector3D &v2); // Distance from vertex
};

#endif /* VECTOR_H */