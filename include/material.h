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
  //construct
  Material()
  Material( double aID, double Den, string Col, string aName)
  //deconstruct
  ~Material()
  void setMaterial( double aID, double Den, string Col, string aName)

  double getID();
  double getDensity();
  string getColour();
  string getName();


};
#endif
