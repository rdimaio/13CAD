#ifndef MATRIX_H
#define MATRIX_H

#include "vector3d.h"
#include <vector>

/**
 * 3x3 matrix.
 */
class Matrix3x3 {
    protected:
        std::vector<float> values;

    public:
        Matrix3x3();
        ~Matrix3x3();

        void setDiagonal(Vector3D &v);
};

#endif /* MATRIX_H */