/**
 * @file matrix.h
 * @brief Header file for the Matrix class
 * @author Riccardo Di Maio
 * @version 1.0 14/12/18
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "vector3d.h"
#include <vector>

/**
 * 3x3 matrix.
 */
class Matrix3x3 {
    protected:
        /**
         * Values that make up the matrix
         */
        std::vector<float> values;

    public:
        Matrix3x3();
        ~Matrix3x3();

        /**
         * Set diagonal of the matrix
         */
        void setDiagonal(Vector3D &v);
};

#endif /* MATRIX_H */