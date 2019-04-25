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

TEST(parseMaterialTest, modelBase) {

	Model mod("tests/ExampleModel.mod");

    std::vector<Material> materials = mod.getMaterials();

    std::string name1 = materials[0].getName();
    std::string colour1 = materials[0].getColour();
    int id1 = materials[0].getId();
    double density1 = materials[0].getDensity();

	ASSERT_EQ(name1, "cu");
    ASSERT_EQ(colour1, "b87333");
    ASSERT_EQ(id1, 0);
    ASSERT_EQ(density1, 8940);
}

TEST(parseVertexTest, modelBase) {

	Model mod("tests/ExampleModel.mod");

    std::vector<Vector3D> vertices = mod.getVertices();

    double x1 = vertices[0].getX();
    double x2 = vertices[1].getX();
    double y1 = vertices[0].getY();
    double y2 = vertices[1].getY();
    double z1 = vertices[0].getZ();
    double z2 = vertices[1].getZ();

    ASSERT_NEAR(x1, 0, 0.009);
    ASSERT_NEAR(y1, -0.3, 0.009);
    ASSERT_NEAR(z1, 0, 0.009);
    ASSERT_NEAR(x2, 0, 0.009);
    ASSERT_NEAR(y2, -0.4, 0.009);
    ASSERT_NEAR(z2, 0, 0.009);
}

TEST(parseCellTest, modelBase) {

	Model mod("tests/ExampleModel.mod");
    std::vector<Cell> cells = mod.getCells();
    std::vector<Vector3D> cellVertices = cells[0].getVertices();

    double x1 = cellVertices[0].getX();
    double y1 = cellVertices[0].getY();
    double z1 = cellVertices[0].getZ();

    ASSERT_NEAR(x1, 0, 0.009);
    ASSERT_NEAR(y1, -0.3, 0.009);
    ASSERT_NEAR(z1, 0, 0.009);
}

TEST(materialCountTest, modelBase) {

    int countExpected = 1;

	Model mod("tests/ExampleModel.mod");

    int countObtained = mod.getMaterialCount();

	ASSERT_EQ(countObtained, countExpected);
}

TEST(vertexCountTest, modelBase) {

    int countExpected = 220;

	Model mod("tests/ExampleModel.mod");

    int countObtained = mod.getVertexCount();

	ASSERT_EQ(countObtained, countExpected);
}

TEST(cellCountTest, modelBase) {

    int countExpected = 100;

	Model mod("tests/ExampleModel.mod");

    int countObtained = mod.getCellCount();

	ASSERT_EQ(countObtained, countExpected);
}
