#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "model.h"

//Code to read file line by line 
//Read first letter and sort into Cell, Material, Vector 

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

					//parseCell(line);				
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
	// strings id:
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
	
	if (id >= this->materials.size()) {
		this->materials.resize(id+1);
	}
	
	this->materials[id] = m;
}

void Model::parseVertex(std::string line) {
	std::vector<std::string> strings = splitString(line);
	// strings id:
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
	
	if (id >= this->vertices.size()) {
		this->vertices.resize(id+1);
	}
	
	this->vertices[id] = v;

}

void Model::parseCell(std::string line) {

	

}

std::vector<Material> Model::getMaterials() {
	return this->materials;
}

std::vector<Vector3D> Model::getVertices() {
	return this->vertices;
}