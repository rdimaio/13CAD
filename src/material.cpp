#include "material.h"

Material::~Material(){}

Material::Material( double aID, double Den, string Col, string aName){
    this->ID = aID;
    this->Density = Den;
    this->Colour = Col;
    this->Name = aName;
  }

void Material::setMaterial( double aID, double Den, string Col, string aName){
    this->ID = aID;
    this->Density = Den;
    this->Colour = Col;
    this->Name = aName;
  }

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
