#include "vector.h"

int main() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    float scalar = 1.5;

    Vector3D vAdd = v1 + v2;
    std::cout << v1 << " + " << v2 << " = " << vAdd << " (expected: [5,7,9])\n";

    Vector3D vSubtract = v1 - v2;
    std::cout << v1 << " - " << v2 << " = " << vSubtract << " (expected: [-3,-3,-3])\n";

    float dot = v1.dot(v2);
    std::cout << v1 << " · " << v2 << " = " << dot << " (expected: 32)\n";

    Vector3D vCross = v1.cross(v2);
    std::cout << v1 << " × " << v2 << " = " << vCross << " (expected: [-3,6,-3])\n";

    Vector3D vScalar_lhs = v1 * scalar;
    std::cout << v1 << " * " << scalar << " = " << vScalar_lhs << " (expected: [1.5,3,4.5])\n";

    Vector3D vScalar_rhs = scalar * v2;
    std::cout << scalar << " * " << v2 << " = " << vScalar_rhs << " (expected: [6,7.5,9])\n";
}