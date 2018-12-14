#include "matrix.h"
#include "vector3d.h"
#include <vector>

void Matrix3x3::setDiagonal(Vector3D &v) {
    this->values.resize(9);
    this->values[1] = this->values[2] = 0.;
    this->values[3] = this->values[5] = 0.;
    this->values[6] = this->values[7] = 0.;
    this->values[0] = v.x;
    this->values[4] = v.y;
    this->values[8] = v.z;
}