#ifndef CELL_H
#define CELL_H

#include <vector>
#include "vector3d.h"

/**
 * Shape defined by 2 or more vertices (Vector3D).
 */
class Cell {
    protected:
        std::vector<Vector3D> vertices;
        double volume;
        double weight;
        // Vector3D centreOfGravity;

        //void updateVolume(); // Update volume only when the size changes
    
    public:
        Cell();
        ~Cell();

		// Accessors
		//virtual double getVolume();
        //virtual double getWeight();
        // Vector3D getCentreOfGravity();
};

/**
 * Pyramid cell, defined by 5 vertices.
 */
class Pyramid : public Cell {
    public:
        Pyramid(std::vector<Vector3D> &vertices);
        ~Pyramid();

		// Accessors
		// virtual double getVolume();
        // virtual double getWeight();
        // Vector3D getCentreOfGravity();
};

/**
 * Hexahedron cell, defined by 8 vertices.
 */
class Hexahedron : public Cell {
    public:
        Hexahedron(std::vector<Vector3D> &vertices);
        ~Hexahedron();

		// Accessors
		//virtual double getVolume();
        //virtual double getWeight();
        // Vector3D getCentreOfGravity();
};

/**
 * Tetrahedron cell, defined by 4 vertices.
 */
class Tetrahedron : public Cell {
    public:
        Tetrahedron(std::vector<Vector3D> &vertices);
        ~Tetrahedron();

		// Accessors
		//virtual double getVolume();
        //virtual double getWeight();
        // Vector3D getCentreOfGravity();
};

#endif /* CELL_H */