#include <iostream>
#include <string>
using namespace std;

#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
	private:
		double ID;
		double Density;
		string Colour;
		string Name;

	public:
		Material();//nor state//
		Material( double aID, double Den, string Col, string aName);
		~Material();
  
		double getID();
		double getDensity();
		string getColour();
		string getName();

		void setID(double aID);
		void setDensity(double Den);
		void setColour(string Col);
		void setName(string aName);
};

#endif
