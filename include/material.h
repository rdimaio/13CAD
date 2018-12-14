#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

/**
 * Material with specific density and colour.
 */
class Material {
	private:
		int id;
		double density;
		std::string colour;
		std::string name;

	public:
		Material(); // Empty initialisation case
		// maybe just do:
		// Material(double id = 0.0, double density = 0.0, etc.)
		Material(int id, double density, std::string colour, std::string name);
		~Material();
  
		// Accessors
		int getId();
		double getDensity();
		std::string getColour();
		std::string getName();

		// Mutators
		void setId(int id);
		void setDensity(double density);
		void setColour(std::string column);
		void setName(std::string name);

		// Operator overloading
        // Note: rhs stands for right hand side
		friend bool operator==(const Material& lhsMaterial, const Material& rhsMaterial);
};

#endif /* MATERIAL_H */
