/**
 * @file cell.cpp
 * @brief Source file for the Cell class and subclasses
 * @author Zong Lei
 * @author Nandi Guo
 * @version 1.0 20/11/18
 */

#include <sstream>
#include "cell.h"
#include "iostream"
#include <vector>
#include "vector3d.h"

Cell::Cell() {}
Cell::~Cell() {}

double Cell::getVolume() {}

double Cell::getMass() {
    double volume = this->getVolume();
    double density = this->material.getDensity();
    double mass = density * volume;
    return mass;
}

std::vector<Vector3D> Cell::getVertices() {
    return this->vertices;
}

Pyramid::Pyramid(std::vector<Vector3D> &vertices, Material &material) {
    for (int i = 0; i < 5; i++) {
        this->vertices.push_back(vertices[i]);
    }
    this->material = material;
}

Pyramid::Pyramid() {}

Pyramid::~Pyramid() {}

double Pyramid::getVolume() {
    double length = vertices[0].distance(vertices[1]);
    double width = vertices[1].distance(vertices[2]);
    Vector3D baseCentre = vertices[0].midpoint(vertices[2]);
    double height = baseCentre.distance(vertices[4]);

    double volume = (length * width * height) / 3;
    return volume;
}

Hexahedron::Hexahedron(std::vector<Vector3D> &vertices, Material &material) {
    for (int i = 0; i < 8; i++) {
        this->vertices.push_back(vertices[i]);
    }
    this->material = material;
}

Hexahedron::Hexahedron() {}

Hexahedron::~Hexahedron() {}

double Hexahedron::getVolume() {
    
}

Tetrahedron::Tetrahedron(std::vector<Vector3D> &vertices, Material &material) {
    for (int i = 0; i < 4; i++) {
        this->vertices.push_back(vertices[i]);
    }
    this->material = material;
}

Tetrahedron::Tetrahedron() {}

Tetrahedron::~Tetrahedron() {}

double Tetrahedron::getVolume() {
    // Source: http://mathworld.wolfram.com/Tetrahedron.html

    Vector3D va = this->vertices[1] - this->vertices[0];
    Vector3D vb = this->vertices[2] - this->vertices[0];
    Vector3D vc = this->vertices[3] - this->vertices[0];

    Vector3D vCross = vb.cross(vc);

    double scalar = va.dot(vCross);

    double volume = scalar/6;

    return volume;
}
