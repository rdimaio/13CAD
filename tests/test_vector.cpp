#include <gtest/gtest.h>
#include "vector3d.h"

// Test parameters
float scalar = 1.5;
Vector3D v1(1, 2, 3);
Vector3D v2(4, 5, 6);

TEST(accessorTest, vectorBase) {
	float xExpected = 1;
	float yExpected = 2;
	float zExpected = 3;

	float xObtained = v1.getX();
	float yObtained = v1.getY();
	float zObtained = v1.getZ();

	ASSERT_EQ(xExpected, xObtained);
	ASSERT_EQ(yExpected, yObtained);
	ASSERT_EQ(zExpected, zObtained);
}

TEST(mutatorTest, vectorBase) {
	Vector3D vBase(4, 5, 6);
	Vector3D vExpected(1, 2, 3);
	vBase.setX(1);
	vBase.setY(2);
	vBase.setZ(3);

	ASSERT_EQ(vBase, vExpected);
}

TEST(additionTest, vectorBase) {
    Vector3D vExpected(5, 7, 9);
    Vector3D vAdd = v1 + v2;
    ASSERT_EQ(vAdd, vExpected);
}

TEST(subtractionTest, vectorBase) {
    Vector3D vExpected(-3, -3, -3);
    Vector3D vSubtract = v1 - v2;
    ASSERT_EQ(vSubtract, vExpected);
}

TEST(equalityTest, vectorBase) {
    Vector3D vEqual(1, 2, 3);
    ASSERT_EQ(v1, vEqual);
}

TEST(dotTest, vectorBase) {
    float dot = v1.dot(v2);
    ASSERT_EQ(dot, 32);
}

TEST(crossTest, vectorBase) {
    Vector3D vExpected(-3, 6, -3);
    Vector3D vCross = v1.cross(v2);
    ASSERT_EQ(vCross, vExpected);
}

TEST(scalarTest, vectorLhs) {
    Vector3D vExpected(1.5, 3, 4.5);
    Vector3D vScalar_lhs = v1 * scalar;
    ASSERT_EQ(vScalar_lhs, vExpected);
}

TEST(scalarTest, vectorRhs) {
    Vector3D vExpected(6, 7.5, 9);
    Vector3D vScalar_rhs = scalar * v2;
    ASSERT_EQ(vScalar_rhs, vExpected);
}
