# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
endif()
endforeach()
PROJECT( QtVTKExample )
# The CMake build process might generate some new files in the current
# directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )
# This allows CMake to run one of Qt's build tools called moc
# if it is needed. moc.exe can be found in Qt's bin directory.
# We'll look at what moc does later.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )
# Find the Qt widgets package. This locates the relevant include and
# lib directories, and the necessary static libraries for linking.
find_package( Qt5Widgets )
set( UIS mainwindow.ui )
qt5_add_resources( QRC_Srcs resource.qrc )
qt5_wrap_ui( UI_Srcs ${UIS} )
# Also link to VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )
# Define the executable output and its sources
add_executable( QtVTKExample MACOSX_BUNDLE
                    main.cpp mainwindow.cpp
                    mainwindow.h
                    mainwindow.ui
                    ${UI_Srcs}
                    ${QRC_Srcs}
)
# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( QtVTKExample Qt5::Widgets )
# Tell CMake that the executable depends on the VTK libraries
target_link_libraries( QtVTKExample ${VTK_LIBRARIES} )
# /CMakeLists.txt-------------------------------------------------------------
