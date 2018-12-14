# ModelLoader/CMakeLists.txt
cmake_minimum_required( VERSION 2.8 )
set(CMAKE_CXX_STANDARD 14)
project(ModelLoader)
set(TEST_PROJECT_NAME Test_ModelLoader)

include_directories( include/
    src/
)

# Set all sources manually (except for main.cpp)
set(SOURCES 
    src/cell.cpp
    src/material.cpp
    src/model.cpp
    src/vector3d.cpp)

option(TESTING "Testing mode" OFF) #OFF by default

if(TESTING)
    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
      message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
      message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                     ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                     EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
      include_directories("${gtest_SOURCE_DIR}/include")
    endif()

    file(GLOB TEST_SOURCES "tests/*.cpp")
    add_executable(${TEST_PROJECT_NAME} ${TEST_SOURCES} ${SOURCES})
    target_link_libraries(${TEST_PROJECT_NAME} gtest_main pthread)
else()
    # Append main.cpp
    list(APPEND SOURCES src/main.cpp)
    add_executable(${PROJECT_NAME} ${SOURCES})
endif(TESTING)

unset(TESTING CACHE)

# / ModelLoader/CMakeLists.txt  
