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

TEST(accessorTest, cellBase) {
    double expectedVolume = 2.67;
    std::vector<Vector3D> vertices;
    Vector3D v1(0.0, 0.0, 0.0);
    Vector3D v2(0.0, -2.0, 0.0);
    Vector3D v3(2.0, -2.0, 0.0);
    Vector3D v4(2.0, 0.0, 0.0);
    Vector3D v5(1.0, -1.0, 2.0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);

    Pyramid pyra(vertices, m0);

    std::vector<Vector3D> verticesObtained = pyra.getVertices();

    for (int i = 0; i < vertices.size(); i++) {
        ASSERT_EQ(vertices[i], verticesObtained[i]);
    }
}

TEST(volumeTest, pyramidBase) {
    double expectedVolume = 2.67;
    std::vector<Vector3D> vertices;
    Vector3D v1(0.0, 0.0, 0.0);
    Vector3D v2(0.0, -2.0, 0.0);
    Vector3D v3(2.0, -2.0, 0.0);
    Vector3D v4(2.0, 0.0, 0.0);
    Vector3D v5(1.0, -1.0, 2.0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);

    Pyramid pyra(vertices, m0);

    double volume = pyra.getVolume();

    ASSERT_NEAR(volume, expectedVolume, 0.009);
}

TEST(massTest, pyramidBase) {
    double expectedMass = 23840;
    std::vector<Vector3D> vertices;
    Vector3D v1(0.0, 0.0, 0.0);
    Vector3D v2(0.0, -2.0, 0.0);
    Vector3D v3(2.0, -2.0, 0.0);
    Vector3D v4(2.0, 0.0, 0.0);
    Vector3D v5(1.0, -1.0, 2.0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);

    Pyramid pyra(vertices, m0);

    double mass = pyra.getMass();

    ASSERT_NEAR(mass, expectedMass, 0.009);
}

TEST(centreTest, pyramidBase) {
    Vector3D centreExpected(1, -1, 0.4);
    std::vector<Vector3D> vertices;
    Vector3D v1(0.0, 0.0, 0.0);
    Vector3D v2(0.0, -2.0, 0.0);
    Vector3D v3(2.0, -2.0, 0.0);
    Vector3D v4(2.0, 0.0, 0.0);
    Vector3D v5(1.0, -1.0, 2.0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);

    Pyramid pyra(vertices, m0);

    Vector3D centreObtained = pyra.getCentre();


	ASSERT_NEAR(centreObtained.getX(), centreExpected.getX(), 0.009);
    ASSERT_NEAR(centreObtained.getY(), centreExpected.getY(), 0.009);
    ASSERT_NEAR(centreObtained.getZ(), centreExpected.getZ(), 0.009);
}

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
    double expectedMass = 11920;
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

TEST(centreTest, tetrahedronBase) {
    Vector3D centreExpected(5.375, 2.125, 1.625);
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

    Vector3D centreObtained = tetra.getCentre();


	ASSERT_NEAR(centreObtained.getX(), centreExpected.getX(), 0.009);
    ASSERT_NEAR(centreObtained.getY(), centreExpected.getY(), 0.009);
    ASSERT_NEAR(centreObtained.getZ(), centreExpected.getZ(), 0.009);
}