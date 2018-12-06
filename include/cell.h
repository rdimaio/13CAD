#pragma once

#include <sstream>
#include <vector>

#include "vector.h"

enum class Shape {
    HEXAHEDRAL, PYRAMIDAL, TETRAHEDRAL
};

std::ostream &operator<<(std::ostream &os, const Shape &shape);

class Material {
public:
    friend std::ostream &operator<<(std::ostream &os, const Material &mat);

    friend std::istream &operator>>(std::istream &in, Material &out);

    int density = -1;
    std::string colour;
    std::string name;
};

class Cell {
public:
    Cell() :
        material(), shape(Shape::HEXAHEDRAL) {};
    Cell(Shape shape, Material material) :
            shape(shape), material(material), vertices() {}

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

    Shape shape;
    Material material;
    std::vector<Vec3> vertices;
};
