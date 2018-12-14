/**
 * @file test_model.cpp
 * @brief Unit tests for the Model class
 * @author Riccardo Di Maio
 * @version 1.0 12/12/18
 */

#include <gtest/gtest.h>
#include "model.h"
#include "material.h"
#include <vector>
#include <string>

TEST(modelTest, modelBase) {

	Model mod("tests/ExampleModel.mod");

    std::vector<Material> materials = mod.getMaterials();

    std::string name1 = materials[0].getName();
    std::string name2 = materials[1].getName();

	ASSERT_EQ(name1, "cu\r");
    ASSERT_EQ(name2, "pkg_plastic\r");
}

TEST(centreTest, modelBase) {
    // [0.00498937,0.00236761,0.00150169]
    Vector3D centreExpected(0.00498937, 0.00236761, 0.00150169);

	Model mod("tests/ExampleModel.mod");

    Vector3D centreObtained = mod.getCentre();

	ASSERT_NEAR(centreObtained.getX(), centreExpected.getX(), 0.009);
    ASSERT_NEAR(centreObtained.getY(), centreExpected.getY(), 0.009);
    ASSERT_NEAR(centreObtained.getZ(), centreExpected.getZ(), 0.009);
}

TEST(materialCountTest, modelBase) {

    int countExpected = 2;

	Model mod("tests/ExampleModel.mod");

    int countObtained = mod.getMaterialCount();

	ASSERT_EQ(countObtained, countExpected);
}

TEST(vertexCountTest, modelBase) {

    int countExpected = 301;

	Model mod("tests/ExampleModel.mod");

    int countObtained = mod.getVertexCount();

	ASSERT_EQ(countObtained, countExpected);
}

TEST(cellCountTest, modelBase) {

    int countExpected = 129;

	Model mod("tests/ExampleModel.mod");

    int countObtained = mod.getCellCount();

	ASSERT_EQ(countObtained, countExpected);
}