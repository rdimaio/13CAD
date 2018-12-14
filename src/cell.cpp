// a cell is defined by a line beginning with a 'c'. The second parameter
// the cell index, the third is a character (either h - hexahedral, p -
// pyramid, t - tetrahedral). Thie 4th in the index of a material that the
// cell is made of and the remaining  numbers state which node defines
// each corner.

#include <sstream>
#include "cell.h"
#include "iostream"
#include <vector>
#include "vector3d.h"

Cell::Cell(){}
Cell::~Cell(){}


Pyramid::Pyramid(std::vector<Vector3D> &vertices) {
    for (int i = 0; i < 5; i++) {
        this->vertices.push_back(vertices[i]);
    }
}

Pyramid::~Pyramid(){}

//double Pyramid::getVolume() {
//    //length = vertices[0].distance(vertices[1]);
//    //width = vertices[1].distance(vertices[2]);
//    //height = 
//}

Hexahedron::Hexahedron(std::vector<Vector3D> &vertices) {
    for (int i = 0; i < 8; i++) {
        this->vertices.push_back(vertices[i]);
    }
}

Hexahedron::~Hexahedron(){}

Tetrahedron::Tetrahedron(std::vector<Vector3D> &vertices) {
    for (int i = 0; i < 4; i++) {
        this->vertices.push_back(vertices[i]);
    }
}

Tetrahedron::~Tetrahedron(){}

/*
std::ostream &operator<<(std::ostream &os, const Cell &cell)
{
    os << cell.shape << "cell made of " << cell.material << "with " << cell.vertices.size() << "vertices";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Shape &shape)
{
    switch (shape) {
		case Shape::HEXAHEDRAL:
            os << "Hexahedral";
            break;
		case Shape::PYRAMIDAL:
            os << "Pyramidal";
            break;
		case Shape::TETRAHEDRAL:
            os << "Tetrahedral";
            break;
		default:
            os << "Broken shape";
    }
    return os;
}

std::istream &operator>>(std::istream &in, Material &out)
{
    in >> out.density;
    in >> out.colour;
    in >> out.name;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Material &mat)
{
    out << mat.name << "with a density of " << mat.density << "with colour " <<  mat.colour;
    return out;
}
*/