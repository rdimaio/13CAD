/**
 * @file cell.h
 * @brief Header file for the Cell class and subclasses
 * @author Zong Lei
 * @author Nandi Guo
 * @version 1.0 20/11/18
 */

#ifndef CELL_H
#define CELL_H

#include <vector>
#include "vector3d.h"
#include "material.h"

/**
 * Shape defined by 2 or more vertices (Vector3D).
 */
class Cell {
    protected:
        std::vector<Vector3D> vertices; // Vertices that define the cell
        Material material;
    
    public:
        Cell();
        ~Cell();

		// Accessors
		virtual double getVolume();
        double getMass();
        std::vector<Vector3D> getVertices();
};

/**
 * Pyramid cell, defined by 5 vertices.
 */
class Pyramid : public Cell {
    public:
        Pyramid();
        Pyramid(std::vector<Vector3D> &vertices, Material &material);
        ~Pyramid();

		// Accessors
		virtual double getVolume();
};

/**
 * Hexahedron cell, defined by 8 vertices.
 */
class Hexahedron : public Cell {
    public:
        Hexahedron();
        Hexahedron(std::vector<Vector3D> &vertices, Material &material);
        ~Hexahedron();

		// Accessors
	    virtual double getVolume();
};

/**
 * Tetrahedron cell, defined by 4 vertices.
 */
class Tetrahedron : public Cell {
    public:
        Tetrahedron();
        Tetrahedron(std::vector<Vector3D> &vertices, Material &material);
        ~Tetrahedron();

		// Accessors
		virtual double getVolume();
};

#endif /* CELL_H */