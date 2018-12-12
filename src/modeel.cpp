#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <Model.h>

include namespace std;

#include "Model.h"

//Supposed to be function for the vector class to be able to load and read the first line of the text file and sort it into the vector class down the line. 
bool Model::Vector () 
{
	int num;
	Vector  v;
	//Reads the first line of the text and if it isnt a V, produces a error mesage 
	if (not(in >> num >> v)) {
		error = "No V in first line ";
		return false;
	}
	//If a V is found in the first line, saves the line in the vector class 
	vertices.emplace(num, v);
	std::cout << " vertex " << num << " " << vertices.at(num) << std::endl;
	return true;
}

//Supposed to be function for the material class to be able to load and read the first line of the text file and sort it into the material class down the line. 

bool Model::Material()
{
	int num;
	Material mat;
	//Reads the first line of the text and if it isnt a V, produces a error mesage
	if (not(in >> num >> mat)) {
		error = "No M in first line";
		return false;
	}
	//If M is found, place it within the M class
	materials.emplace(num, mat);
	std::cout << " material " << num << " " << materials.at(num) << std::endl;
	return true;
}
//reads the first line and sorts the line into Cell if C is the first line
bool Model::Cell()
{
	std::stringstream in(line);
	int num;
	char shapeLetter;
	int materialNum;
//if C isnt found int the first line, it gets ignored. 
	in.ignore(1, ' ');
	if (not(in >> num >> shapeLetter >> materialNum)) {
		error = "no C in first line";
		return false;
	}

//Sorts the Cell class between Tetrahedron, Hexahedron or Pyramid depending on the number of vertices 
	int numberOfVertices = 0;
	switch (shapeLetter) {
	case 'h':
		shape = Shape::HEXAHEDRAL;
		numberOfVertices = 8;
		break;
	case 'p':
		shape = Shape::PYRAMIDAL;
		numberOfVertices = 5;
		break;
	case 't':
		shape = Shape::TETRAHEDRAL;
		numberOfVertices = 4;
		break;
	default:
		error = "Invalid shape in file";
		return false;
	}
	if (materials.count(materialNum) == 0) {
		error = "Invalid material number in file";
		return false;
	}

Model::Model(const std::string fileName) : // Model File name
	fileName(fileName)
{};



