# CMakeLists.txt---------------------------------------------------------------
cmake_minimum_required( VERSION 2.8 )
PROJECT( Cube )
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )
add_executable( Cube vtk_cube.cpp )
target_link_libraries( Cube ${VTK_LIBRARIES} )
# /CMakeLists.txt--------------------------------------------------------------