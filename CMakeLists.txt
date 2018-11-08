# ModelLoader/CMakeLists.txt
cmake_minimum_required( VERSION 2.8 )
project(ModelLoader)

include_directories( include/
    src/
)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# / ModelLoader/CMakeLists.txt  