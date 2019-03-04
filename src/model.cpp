#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <Model.h>


#include "model.h"
#include "Result.h"


bool Model::parseVertex(const std::string line, std::string &error)
{
    std::stringstream in(line);
    int num;
    Vector3D v;
    in.ignore(1, ' ');
    if (not(in >> num >> v)) {
        error = "Error parsing vertex from file";
        return false;
    }
    vertices.emplace(num, v);
    std::cout << "Parsed vertex " << num << " " << vertices.at(num) << std::endl;
    return true;
}

bool Model::parseMaterial(std::string line, std::string &error)
{
    std::stringstream in(line);
    int num;
    Material mat;
    in.ignore(1, ' ');
    if (not(in >> num >> mat)) {
        error = "Error parsing material from file";
        return false;
    }
    materials.emplace(num, mat);
    std::cout << "Parsed material " << num << " " << materials.at(num) << std::endl;
    return true;
}

bool Model::parseCell(std::string line, std::string &error)
{
    std::stringstream in(line);
    int num;
    char shapeLetter;
    int materialNum;
    Shape shape;
    in.ignore(1, ' ');
    if (not(in >> num >> shapeLetter >> materialNum)) {
        error = "Error parsing cell from file";
        return false;
    }

    int numberOfVertices = 0;
    switch (shapeLetter) {
        case 'h':
            shape = Shape::HEXAHEDRAL;
            numberOfVertices = 8;
            break;
        case 'p':
            shape = Shape::PYRAMIDAL;
            numberOfVertices = 5;
            break;
        case 't':
            shape = Shape::TETRAHEDRAL;
            numberOfVertices = 4;
            break;
        default:
            error = "Invalid shape in file";
            return false;
    }
    if (materials.count(materialNum) == 0) {
        error = "Invalid material number in file";
        return false;
    }

    Cell cell(shape, materials.at(materialNum));

    int vertexNum;
    while (in >> vertexNum) {
        if (vertices.find(vertexNum) != vertices.end()) {
            cell.vertices.push_back(vertices.at(vertexNum));
        } else {
            error = "Invalid vertex number in file";
            return false;
        }
    }
    if (cell.vertices.size() != numberOfVertices) {
        error = "Wrong number of vertices for shape in file";
        return false;
    }

    cells.emplace(num, std::move(cell));
    std::cout << "Parsed cell " << num << " " << cells.at(num) << std::endl;
    return true;
}

Model::Model(const std::string fileName) :
        fileName(fileName)
{};

Result<Model> Model::load()
{
    std::ifstream file(fileName);
    if (!file.is_open())
        return {false, {}, "File Not Found"};

    std::string line;
    int lineNum = 0;
    bool success;
    std::string error = "Unknown Error";

    while (std::getline(file, line)) {
        lineNum++;
        switch (line.front()) {
            case '\n':
            case '\r':
            case '\0':
            case '#':
                success = true;
                break;
            case 'm':
                success = parseMaterial(line, error);
                break;
            case 'v':
                success = parseVertex(line, error);
                break;
            case 'c':
                success = parseCell(line, error);
                break;
            default:
                error = "Invalid start character in file";
                success = false;
                break;
        }
        if (not success) {
            error += " at line ";
            error += std::to_string(lineNum);
            return {false, {}, error};
        }
    }
    return {true, *this};
}

uint64_t Model::numVertices()
{
    return vertices.size();
}

uint64_t Model::numCells()
{
    return cells.size();
}

uint64_t Model::numMaterials()
{
    return materials.size();
}

void Model::describeCells()
{
    std::cout << cells.size() << " Cells:" << std::endl;
    for (auto &cellKey : cells)
        std::cout << "Cell " << cellKey.first << ": " << cellKey.second << std::endl;
}

void Model::describeVertices()
{
    std::cout << vertices.size() << " Vertices:" << std::endl;
    for (auto &vertexKey : vertices)
        std::cout << "Vertex " << vertexKey.first << ": " << vertexKey.second << std::endl;
}

void Model::describeMaterials()
{
    std::cout << materials.size() << " Materials:" << std::endl;
    for (auto &matKey : materials)
        std::cout << "Material " << matKey.first << ": " << matKey.second << std::endl;
}

std::vector<int> Model::cellIDs()
{
    std::vector<int> ids;
    for (auto cellKey : cells)
        ids.push_back(cellKey.first);
    return std::move(ids);
}

bool Model::cellExists(int id)
{
    return cells.find(id) != cells.end();
}

Result<Cell> Model::getCell(int id)
{
    if (cellExists(id))
        return {true, cells.at(id)};
    else
        return {false, {}, "Cell " + std::to_string(id) + " accessed which does not exist"};
}
