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
    std::string name2 = materials[1].getName();
    std::string colour1 = materials[0].getColour();
    std::string colour2 = materials[1].getColour();
    int id1 = materials[0].getId();
    int id2 = materials[1].getId();
    double density1 = materials[0].getDensity();
    double density2 = materials[1].getDensity();

	ASSERT_EQ(name1, "cu");
    ASSERT_EQ(name2, "pkg_plastic");
    ASSERT_EQ(colour1, "b87333");
    ASSERT_EQ(colour2, "000000");
    ASSERT_EQ(id1, 0);
    ASSERT_EQ(id2, 1);
    ASSERT_EQ(density1, 8940);
    ASSERT_EQ(density2, 100);
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

    ASSERT_NEAR(x1, 0.00195, 0.009);
    ASSERT_NEAR(y1, 0.00115, 0.009);
    ASSERT_NEAR(z1, 0.0015, 0.009);
    ASSERT_NEAR(x2, 0.00295, 0.009);
    ASSERT_NEAR(y2, 0.00115, 0.009);
    ASSERT_NEAR(z2, 0.0015, 0.009);
}

TEST(parseCellTest, modelBase) {

	// TODO: see from tests above
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

//TEST(accessorTest, modelBase) {
//
//    std::string filenameExpected = "tests/ExampleModel.mod";
//
//	Model mod("tests/ExampleModel.mod");
//
//    std::string filenameObtained = mod.getFilename();
//
//	ASSERT_EQ(filenameExpected, filenameObtained);
//}

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
