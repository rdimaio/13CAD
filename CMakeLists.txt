# ModelLoader/CMakeLists.txt
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)

foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

project(ModelLoader)
set(TEST_PROJECT_NAME Test_ModelLoader)

include_directories( include/
    src/
)

# The CMake build process might generate some new files in the current
# directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )


# This allows CMake to run one of Qt's build tools called moc
# if it is needed. moc.exe can be found in Qt's bin directory.
# We'll look at what moc does later.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

# Set all sources manually (except for main.cpp)
set(SOURCES 
    src/cell.cpp
    src/material.cpp
    src/matrix.cpp
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

    # Find the Qt widgets package. This locates the relevant include and
    # lib directories, and the necessary static libraries for linking.
    find_package( Qt5Widgets )

    set( UIS src/gui/mainwindow.ui src/gui/helpdialog.ui src/gui/clipdialog.ui)
    qt5_wrap_ui( UI_Srcs ${UIS} )

    set( ICONS src/gui/icons/icons.qrc )
    qt5_add_resources( QRC_Srcs ${ICONS} )

    # Also link to VTK
    # find_package( VTK REQUIRED)
    find_package(VTK REQUIRED)
    if (NOT VTK_FOUND)
      message("Skipping ReadSTL: ${VTK_NOT_FOUND_MESSAGE}")
      return ()
    endif()
    
    message (STATUS "VTK_VERSION: ${VTK_VERSION}")

    include( ${VTK_USE_FILE} )

    # Append main.cpp
    list(APPEND SOURCES 
      src/main.cpp
      src/gui/mainwindow.cpp 
		  src/gui/mainwindow.h 
      src/gui/mainwindow.ui
      src/gui/helpdialog.cpp
      src/gui/helpdialog.h
      src/gui/helpdialog.ui
      src/gui/clipdialog.cpp
      src/gui/clipdialog.h
      src/gui/clipdialog.ui)
      add_executable(${PROJECT_NAME} MACOSX_BUNDLE 
      ${SOURCES}
      ${UI_Srcs}
      ${QRC_Srcs}
    )

    target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${VTK_LIBRARIES})

    install(TARGETS ${PROJECT_NAME}
      RUNTIME DESTINATION bin
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib/static)

    # Use NSIS to generate installer for Windows, else format it to Zip
    if(WIN32)
	  file(GLOB DLL_FILES ${DLL_DIR}/*.dll)
      install(FILES ${DLL_FILES} DESTINATION bin)
      set(CPACK_GENERATOR "NSIS")
    else()
      set(CPACK_GENERATOR "ZIP")
    endif()
    include(CPack)

endif(TESTING)

unset(TESTING CACHE)

# / ModelLoader/CMakeLists.txt  