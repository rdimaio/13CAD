#include <gtest/gtest.h>
#include "model.h"
#include "material.h"
#include <vector>
#include <string>

TEST(modelTest, modelBase) {

	Model m("tests/ExampleModel.mod");

    std::vector<Material> materials = m.getMaterials();

    std::string name1 = materials[0].getName();
    std::string name2 = materials[1].getName();

	ASSERT_EQ(name1, "test");
    ASSERT_EQ(name2, "pkg_plastic");