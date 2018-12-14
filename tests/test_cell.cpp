/**
 * @file test_cell.cpp
 * @brief Unit tests for the Cell class and subclasses
 * @author Riccardo Di Maio
 * @version 1.0 14/12/18
 */

#include <gtest/gtest.h>
#include "cell.h"
#include "vector3d.h"

TEST(volumeTest, tetrahedronBase) {
    double expectedVolume = 1.33;
    std::vector<Vector3D> vertices;
    Vector3D v1(5.0, 0.0, 0.0);
    Vector3D v2(5.0, 1.0, 1.0);
    Vector3D v3(6.0, 1.0, 5.0);
    Vector3D v4(5.5, 6.5, 0.5);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);

    Tetrahedron tetra(vertices);

    double volume = tetra.getVolume();

    ASSERT_DOUBLE_EQ(volume, expectedVolume);
}