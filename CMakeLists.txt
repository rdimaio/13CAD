# ModelLoader/CMakeLists.txt
cmake_minimum_required( VERSION 2.8 )
project(ModelLoader)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories( include/
    src/
)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)

# / ModelLoader/CMakeLists.txt  