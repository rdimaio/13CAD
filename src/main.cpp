#include <iostream>
#include <string>
#include <vector>

#include "cell.h"
#include "material.h"
#include "matrix.h"
#include "model.h"
#include "vector3d.h"

int main()
{
    Model mod("tests/ExampleModel.mod");
    mod.saveToFile("tests/test.mod");
    
    return 0;
}