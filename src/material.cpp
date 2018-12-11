#include "material.h"

Material::Material(){ 

    // Initialise variables
    this->id=0.0;
    this->density=0.0;
}

Material::Material(double id, double density, string column, string name){
    this->id = id;
    this->density = density;
    this->colour = column;
    this->name = name;
}

Material::~Material(){}

double Material::getId(){
    return this->id;
}

double Material::getDensity(){
    return this->density;
}

string Material::getColour(){
    return this->colour;
}

string Material::getName(){
    return this->name;
}

void Material::setId(double id){
    this->id = id;
}

void Material::setDensity(double density){
    this->density = density;
}

void Material::setColour(string Col){
    this->colour = colour;
}

void Material::setName(string aName){
    this->name = name;
}
