/**
 * @file model.h
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
        /**
         * Name of file to load
         */
        std::string filename;
    
        /**
         * True if the file is a STL file (.stl extension)
         */
        bool isSTL;

        /**
         * std::vector of vertices loaded from file
         */
        std::vector<Vector3D> vertices;

        /**
         * std::vector of materials loaded from file
         */
        std::vector<Material> materials;
        
        /**
         * std::vector of cells loaded from file
         */
        std::vector<Cell> cells;
    
        // Parsing functions

        /**
         * Parse vertex string
         */
        void parseVertex(std::string line);

        /**
         * Parse material string
         */
        void parseMaterial(std::string line);
        
        /**
         * Parse cell string
         */
        void parseCell(std::string line);

        // Misc functions
        /**
         * Split string into space-separated words
         */
        std::vector<std::string> splitString(std::string line);
        
        /**
         * Return true if file is of that extension.
         */
        bool isExtension(const std::string &str, const std::string &suffix);
    
    public:
        Model() = default;
        ~Model() = default;
        // Loads model from file
        Model(std::string filename);

        // Accessors

        /**
         * Get model's filename
         */
        std::string getFilename();

        /**
         * Return true if model is a .STL file
         */
        bool getIsSTL();

        /**
         * Get list of materials as a std::vector
         */
        std::vector<Material> getMaterials();

        /**
         * Get list of vertices as a std::vector
         */
        std::vector<Vector3D> getVertices();

        /**
         * Get list of cells as a std::vector
         */
        std::vector<Cell> getCells();

        /**
         * Get total number of materials
         */
        int getMaterialCount();

        /**
         * Get total number of vertices
         */
        int getVertexCount();

        /**
         * Get total number of cells
         */
        int getCellCount();

        /**
         * Return a string with the total number of cells
         * and, for each cell, its ID and type
         */
        std::string getCellList();

        /**
         * Get the centre of the model based on the vertices
         */
        Vector3D getCentre();

        // Misc functions

        /**
         * Copy current model to another file (just copies the contents of the input file)
         */
        void copyToFile(std::string filename);

        /**
         * Save current model to file
         */
        void saveToFile(std::string filename);

    
};

#endif /* MODEL_H */