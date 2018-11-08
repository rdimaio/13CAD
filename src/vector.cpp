#include <cmath>

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

        // Operator overloading
        // Note: rhs stands for right hand side
        Vector3D operator+(Vector3D rhsVector);
        Vector3D operator-(Vector3D rhsVector);
        float operator*(Vector3D rhsVector); // Dot product
        // Scalar multiplication
        Vector3D operator*(float scalar); // Vector on lhs
        friend Vector3D operator*(float scalar, Vector3D v); // Vector on rhs

};

Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
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

// Scalar multiplication - vector on lhs
Vector3D Vector3D::operator*(float scalar) {
    Vector3D result(this->x * scalar, this->y * scalar, this->z * scalar);
    return result;
}

// Scalar multiplication - vector on rhs
Vector3D operator*(float scalar, Vector3D v) {
    Vector3D result(v.x * scalar, v.y * scalar, v.z * scalar);
    return result;
}

// Dot product
float Vector3D::operator*(Vector3D rhsVector) {
    float result = this->x * rhsVector.x + this->y * rhsVector.y + this->z * rhsVector.z;
    return result;
}
