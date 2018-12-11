#ifndef MATERIAL_H
#define MATERIAL_H




/**
 * Material with specific density and colour.
 */
class Material {
	private:
		double id;
		double density;
		std::string colour;
		std::string name;

	public:
		Material(); // Empty initialisation case
		Material(double id, double density, std::string colour, std::string name);
		~Material();
  
		// Accessors
		double getId();
		double getDensity();
		std::string getColour();
		std::string getName();

		// Mutators
		void setId(double id);
		void setDensity(double density);
		void setColour(std::string column);
		void setName(std::string name);

		// Operator overloading
        // Note: rhs stands for right hand side
		friend bool operator==(const Material& lhsMaterial, const Material& rhsMaterial);
};

#endif
