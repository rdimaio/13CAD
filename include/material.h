#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <string>
using namespace std;


/**
 * Material with specific density and colour.
 */
class Material {
	private:
		double id;
		double density;
		string colour;
		string name;

	public:
		Material(); // Empty initialisation case
		Material(double id, double density, string colour, string name);
		~Material();
  
		// Accessors
		double getId();
		double getDensity();
		string getColour();
		string getName();

		// Mutators
		void setId(double id);
		void setDensity(double density);
		void setColour(string column);
		void setName(string name);
};

#endif
