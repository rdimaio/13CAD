/**
 * @file test_cell.cpp
 * @brief Unit tests for the Cell class and subclasses
 * @author Riccardo Di Maio
 * @version 1.0 14/12/18
 */

#include <gtest/gtest.h>
#include "cell.h"
#include "material.h"
#include "vector3d.h"

// Test parameters
Material m0(0, 8940, "b87333", "cu");

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

    Tetrahedron tetra(vertices, m0);

    double volume = tetra.getVolume();

    ASSERT_NEAR(volume, expectedVolume, 0.009);
}

TEST(massTest, tetrahedronBase) {
    double expectedMass = 11890.2;
    std::vector<Vector3D> vertices;
    Vector3D v1(5.0, 0.0, 0.0);
    Vector3D v2(5.0, 1.0, 1.0);
    Vector3D v3(6.0, 1.0, 5.0);
    Vector3D v4(5.5, 6.5, 0.5);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);

    Tetrahedron tetra(vertices, m0);

    double mass = tetra.getMass();

    ASSERT_NEAR(mass, expectedMass, 0.009);
}