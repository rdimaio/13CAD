/**
 * @file material.h
 * @brief Header file for the Material class
 * @author Tanchanok Srisung
 * @version 1.0 15/11/18
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

/**
 * Material with specific density and colour.
 */
class Material {
	private:

		/**
		 * ID that uniquely identifies the material
		 */
		int id;

		/**
		 * Density of the material
		 */
		double density;

		/**
		 * Colour of the material
		 */
		std::string colour;

		/**
		 * Name of the material
		 */
		std::string name;

	public:
		Material(); // Empty initialisation case
		// maybe just do:
		// Material(double id = 0.0, double density = 0.0, etc.)
		Material(int id, double density, std::string colour, std::string name);
		~Material();
  
		// Accessors

		/**
		 * Return material's ID
		 */
		int getId();

		/**
		 * Return material's density
		 */
		double getDensity();

		/**
		 * Return material's colour
		 */
		std::string getColour();

		/**
		 * Return material's name
		 */
		std::string getName();

		// Mutators

		/**
		 * Set material's ID
		 */
		void setId(int id);

		/**
		 * Set material's density
		 */
		void setDensity(double density);

		/**
		 * Set material's colour
		 */
		void setColour(std::string colour);

		/**
		 * Set material's name
		 */
		void setName(std::string name);

		// Operator overloading
        // Note: rhs stands for right hand side

		/**
		 * Equality operator between two materials
		 */
		friend bool operator==(const Material& lhsMaterial, const Material& rhsMaterial);
};

#endif /* MATERIAL_H */
