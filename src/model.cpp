#include <iostream>
#include <fstream>
#include <sstream>
#include <Model.h>
#include <iostream>

//Code to read file line by line 
//Read first letter and sort into Cell, Material, Vector 




void Model::loadFromFile(const char *filename) {  // or string class?

	// open file

	// loop thru each line4
		// decide is line cell/model/vector etc
		// process line and create new class of correct type
	if (lineType == CELL) {
		Cell c;

		c.id = [value read from file...0];
		c.

			this->cells.push_back(c);

	}
		// add class to arrays
}

//Cell code
void Model::setCell( int i, Cell &c ) {
	// set cell with id i to be equal to c

}


Cell Model::sgetCell(int i) {
	// get cell with id i 

}

/*
//Materia Code
SetMaterial{};
GetMaterial{};


//Vector Code 
SetVector{};
GetCell{};
*/