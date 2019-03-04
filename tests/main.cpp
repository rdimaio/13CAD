<<<<<<< HEAD
#include "vector.h"
#include "model.h"
#include "cell.h"
#include <gtest/gtest.h>

// Test parameters
float scalar = 1.5;
Vector3D v1(1, 2, 3);
Vector3D v2(4, 5, 6);
Cell v1(h, 0, 0, 1, 2, 3, 4, 5, 6, 7);

TEST(accessorTest, base) {
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

TEST(mutatorTest, base) {
	Vector3D vBase(4, 5, 6);
	Vector3D vExpected(1, 2, 3);
	vBase.setX(1);
	vBase.setY(2);
	vBase.setZ(3);

	ASSERT_EQ(vBase, vExpected);
}
=======
/**
 * @file main.cpp
 * @brief Main file for the unit tests, runs all the unit tests together
 * @author Riccardo Di Maio
 * @version 1.0 10/12/18
 */
>>>>>>> origin

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
