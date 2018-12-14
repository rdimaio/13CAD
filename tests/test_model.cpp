#include <gtest/gtest.h>
#include "model.h"
#include "material.h"
#include <vector>
#include <string>

TEST(modelTest, modelBase) {

	Model m("ExampleModel.mod");

    std::vector<Material> materials = m.getMaterials();

    std::string name1 = materials[0].getName();

	ASSERT_EQ(name1, "test");
}