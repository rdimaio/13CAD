#include "material.h"

#include <string>

Material::Material(){ 

    // Initialise variables
    this->id=0.0;
    this->density=0.0;
}

Material::Material(double id, double density, std::string column, std::string name){
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

std::string Material::getColour(){
    return this->colour;
}

std::string Material::getName(){
    return this->name;
}

void Material::setId(double id){
    this->id = id;
}

void Material::setDensity(double density){
    this->density = density;
}

void Material::setColour(std::string colour){
    this->colour = colour;
}

void Material::setName(std::string name){
    this->name = name;
}

bool operator==(const Material& lhsMaterial, const Material& rhsMaterial) {
        if (lhsMaterial.id == rhsMaterial.id && lhsMaterial.density == rhsMaterial.density && lhsMaterial.colour == rhsMaterial.colour && lhsMaterial.name == rhsMaterial.name) {
        return true;
    } else {
        return false;
    }
}