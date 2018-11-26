//fnc declare//
#include <iostream>
#include <string>//string//
using namespace std;
#define MATERIAL_H
#ifndef MATERIAL_H //if not define//

//class//
class Material {
private://no change outwhere in the program//
//member variables//
  double ID;
  double Density;
  string Colour;
  string Name;

public://declaration//
  Material();//nor state//
  Material( double aID, double Den, string Col, string aName);
  ~Material();
  //get=return//
  double getID();
  double getDensity();
  string getColour();
  string getName();

  void setID( double aID);
  void setDensity( double Den);
  void setColour( string Col);
  void setName( string aName);
};

#endif
