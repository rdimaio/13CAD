#ifndef MODEL_H
#define MODEL_H

#include <map>
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
    
        // std::vectors can be faster than std::map; each model will have
        // an unique id for every vertex, material and cell anyway
    
        std::vector<Vector3D> vertices;
        std::vector<Material> materials;
        std::vector<Cell> cells;
    
        void parseVertex(std::string line);
        void parseMaterial(std::string line);
        void parseCell(std::string line);
        std::vector<std::string> splitString(std::string line);
    
    public:
        Model() = default;
        ~Model() = default;
        Model(std::string filename);

        std::vector<Material> getMaterials();
        std::vector<Vector3D> getVertices();
    
};

#endif /* MODEL_H */