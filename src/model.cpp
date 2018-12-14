/**
 * @file model.cpp
 * @brief Source file for the Model class
 * @author Daniel Msimuko
 * @version 1.0 08/12/18
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "vector3d.h"
#include "cell.h"
#include "model.h"

Model::Model(std::string filename) {
	std::ifstream modelFile(filename);
	std::string line;
	
	if (modelFile.is_open()) {
		// Read file line by line
		while (std::getline(modelFile, line)) {
			// Check first character
    		switch (line[0]) {
				// Cell case
				case 'c':
					parseCell(line);				
					break;

				// Vertex case
				case 'v':
					parseVertex(line);
					break;

				// Material case
				case 'm':
					parseMaterial(line);
					break;
			}
		}
		modelFile.close();
	}
}

/**
 * Split string into space-separated words.
 */
std::vector<std::string> Model::splitString(std::string line) {
	std::vector<std::string> strings; 
	std::istringstream f(line);
	std::string s;
	
	// Split string into space-separated words
	while (std::getline(f, s, ' ')) {
        strings.push_back(s);
    }
	return strings;
}

void Model::parseMaterial(std::string line) {

	std::vector<std::string> strings = splitString(line);
	// Strings index:
	// 0 - m
	// 1 - ID
	// 2 - Density
	// 3 - Colour
	// 4 - Name
	
	int id = std::stoi(strings[1]);
	double density = std::stod(strings[2]);
	std::string colour = strings[3];
	std::string name = strings[4];

	Material m(id, density, colour, name);
	
	// Resize materials vector if necessary
	if (id >= this->materials.size()) {
		this->materials.resize(id+1);
	}
	
	this->materials[id] = m;
}

void Model::parseVertex(std::string line) {
	std::vector<std::string> strings = splitString(line);
	// Strings index:
	// 0 - v
	// 1 - ID
	// 2 - x
	// 3 - y
	// 4 - z
	
	int id = std::stoi(strings[1]);
	float x = std::stod(strings[2]);
	float y = std::stod(strings[3]);
	float z = std::stod(strings[4]);
	
	Vector3D v(x, y, z);
	
	// Resize vertices vector if necessary
	if (id >= this->vertices.size()) {
		this->vertices.resize(id+1);
	}
	
	this->vertices[id] = v;
}

void Model::parseCell(std::string line) {
	std::vector<std::string> strings = splitString(line);
	// Strings index:
	// 0 - c
	// 1 - ID
	// 2 - cell type:
	//	   h - hexahedral
	//	   p - pyramid
	//     t - tetrahedral
	// 3 - Material ID
	// 4 and onwards - IDs of vertices which define the cell

	int matId = std::stoi(strings[3]);
	Material mat = this->materials[matId];

	std::vector<Vector3D> vertices;

	// Fill vertices ID with the required IDs
	for (int i = 4; i < strings.size(); i++) {
		int vertexId = std::stoi(strings[i]);
		Vector3D vertex = this->vertices[vertexId];
		vertices.push_back(vertex);
	}
	// Check cell type
	// Note: curly braces are to prevent initializators from leaking in
	// other cases (also causes compiler error)
    switch (strings[2][0]) {
		// Hexahedral case
		case 'h': {
			Hexahedron(vertices, mat);		
			break;
		}
		// Pyramid case
		case 'p': {
			Pyramid(vertices, mat);
			break;
		}
		// Tetrahedral case
		case 't': {
			Tetrahedron(vertices, mat);
			break;
		}
	}

}

std::string Model::getFilename() {
	return this->filename;
}

std::vector<Material> Model::getMaterials() {
	return this->materials;
}

std::vector<Vector3D> Model::getVertices() {
	return this->vertices;
}

std::vector<Cell> Model::getCells() {
	return this->cells;
}

// Save model to specified filename
//void Model::saveToFile(std::string filename) {
//	std::vector<Material> materials = this.getMaterials();
//}