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

    ASSERT_EQ(volume, expectedVolume);
}