#include <iostream>
#include "model.h"
#include "material.h"
#include <vector>
#include <string>

int main()
{
    std::cout << "test1" << std::endl;
   	Model mod("tests/ExampleModel.mod");
    std::cout << "test2" << std::endl;
    std::vector<Material> materials = mod.getMaterials();
    std::vector<Vector3D> vertices = mod.getVertices();

    std::string name1 = materials[0].getName();

    std::cout << name1 << std::endl;
    std::cout << vertices[5].getZ() << std::endl;
    std::cout << vertices.size() << std::endl;

    return 0;

}