#include <iostream>
#include "model.h"
#include "material.h"
#include "cell.h"
#include "vector3d.h"
#include <vector>
#include <string>

int main()
{
    //std::cout << "test1" << std::endl;
   	//Model mod("tests/ExampleModel.mod");
    //std::cout << "test2" << std::endl;
    //std::vector<Material> materials = mod.getMaterials();
    //std::vector<Vector3D> vertices = mod.getVertices();
//
    //std::string name1 = materials[0].getName();
//
    //std::cout << name1 << std::endl;
    //std::cout << vertices[5].getZ() << std::endl;
    //std::cout << vertices.size() << std::endl;

    // Test parameters
Material m0(0, 8940, "b87333", "cu");

    std::vector<Vector3D> vertices;
    Vector3D v1(5.0, 0.0, 0.0);
    Vector3D v2(5.0, 1.0, 1.0);
    Vector3D v3(6.0, 1.0, 5.0);
    Vector3D v4(5.5, 6.5, 0.5);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);

    Tetrahedron tetra(vertices, m0);

    double volume = tetra.getVolume();
    double mass = tetra.getMass();
    std::cout << volume << std::endl;

    std::cout << mass << std::endl;

    return 0;

}