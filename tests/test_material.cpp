/**
 * @file test_material.cpp
 * @brief Unit tests for the Material class
 * @author Riccardo Di Maio
 * @version 1.0 10/12/18
 */

#include <gtest/gtest.h>
#include "material.h"

// Test parameters
Material m1(1, 5, "brown", "bronze");

TEST(accessorTest, materialBase) {
	float idExpected = 1;
	float densityExpected = 5;
	std::string colourExpected = "brown";
    std::string nameExpected = "bronze";

	float idObtained = m1.getId();
	float densityObtained = m1.getDensity();
	std::string colourObtained = m1.getColour();
    std::string nameObtained = m1.getName();

	ASSERT_EQ(idExpected, idObtained);
	ASSERT_EQ(densityExpected, densityObtained);
	ASSERT_EQ(colourExpected, colourObtained);
    ASSERT_EQ(nameExpected, nameObtained);
}

TEST(mutatorTest, materialBase) {
	Material mBase(4, 14.184, "silver", "mercury");
	Material mExpected(1, 19.30, "yellow gold", "gold");
	mBase.setId(1);
	mBase.setDensity(19.30);
	mBase.setColour("yellow gold");
    mBase.setName("gold");

	ASSERT_EQ(mBase, mExpected);
}

TEST(equalityTest, materialBase) {
    Material mEqual(1, 5, "brown", "bronze");
    ASSERT_EQ(m1, mEqual);
}