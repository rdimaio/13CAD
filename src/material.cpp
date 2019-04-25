/**
 * @file material.cpp
 * @brief Source file for the Material class
 * @author Tanchanok Srisung
 * @version 1.0 15/11/18
 */

#include "material.h"
#include <string>

Material::Material()
{

    // Initialise variables
    this->id = 0;
    this->density = 0.0;
}

Material::Material(int id, double density, std::string column, std::string name)
{
    this->id = id;
    this->density = density;
    this->colour = column;
    this->name = name;
}

Material::~Material() {}

int Material::getId()
{
    return this->id;
}

double Material::getDensity()
{
    return this->density;
}

std::string Material::getColour()
{
    return this->colour;
}

std::string Material::getName()
{
    return this->name;
}

void Material::setId(int id)
{
    this->id = id;
}

void Material::setDensity(double density)
{
    this->density = density;
}

void Material::setColour(std::string colour)
{
    this->colour = colour;
}

void Material::setName(std::string name)
{
    this->name = name;
}

bool operator==(const Material &lhsMaterial, const Material &rhsMaterial)
{
    if (lhsMaterial.id == rhsMaterial.id && lhsMaterial.density == rhsMaterial.density && lhsMaterial.colour == rhsMaterial.colour && lhsMaterial.name == rhsMaterial.name)
    {
        return true;
    }
    else
    {
        return false;
    }
}