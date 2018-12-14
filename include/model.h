/**
 * @file model.cpp
 * @brief Header file for the Model class
 * @author Daniel Msimuko
 * @version 1.0 08/12/18
 */

#ifndef MODEL_H
#define MODEL_H

#include <string>

#include "vector3d.h"
#include "cell.h"
#include "material.h"

/**
 * Model that loads vectors and cells from files.
 */
class Model {
    private:
        std::string filename;
    
        // Vectors that hold the model's information
        std::vector<Vector3D> vertices;
        std::vector<Material> materials;
        std::vector<Cell> cells;
    
        // Parsing functions
        void parseVertex(std::string line);
        void parseMaterial(std::string line);
        void parseCell(std::string line);

        // Misc functions
        std::vector<std::string> splitString(std::string line);
    
    public:
        Model() = default;
        ~Model() = default;
        // Loads model from file
        Model(std::string filename);

        // Accessors
        std::string getFilename();
        std::vector<Material> getMaterials();
        std::vector<Vector3D> getVertices();
        std::vector<Cell> getCells();
        //int getMaterialCount();
        //int getVerticesCount();
        //int getCellCount();
//
        //// Misc functions
        //void saveToFile(std::string filename);

    
};

#endif /* MODEL_H */