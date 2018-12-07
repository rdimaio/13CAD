//fnc def//

#include "Material.h"

Material::Material(){ //class
  //set member variables to nor state but the string is already equal nor state
  this->ID=0.0;//initialize
  this->Density=0.0;//initialize
}

Material::Material( double aID, double Den, string Col, string aName){
    this->ID = aID;
    this->Density = Den;
    this->Colour = Col;
    this->Name = aName;
  }

Material::~Material(){}

double Material::getID(){
    return this->ID;
  }
double Material::getDensity(){
    return this->Density;
  }
string Material::getColour(){
    return this->Colour;
  }
string Material::getName(){
    return this->Name;
  }

void Material::setID ( double aID){
    this->ID = aID;
  }
void Material::setDensity ( double Den){
    this->Density = Den;
  }
void Material::setColour ( double Col){
    this->Colour = Col;
  }
void Material::setName ( double aName){
    this->Name = aName;
  }
