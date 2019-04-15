When you start Command Prompt:
------------------------------------------------------------------------------------------
C:\Users\ezydhm\Desktop\H62PEP-Week1\Worksheet6\qtvtk-master
----------------------------------
###################################################################
Then follow these commands:
----------------------------------
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

set PATH=%PATH%;C:\Qt\5.12.1\msvc2017\bin;"C:/Users/ezydhm/Desktop/VTK-8.2.0/VTK-8.2.0/build/Debug"

cmake -DCMAKE_PREFIX_PATH="C:/program files (x86)/vtk/bin";"C:\Qt\5.12.1\msvc2017" -G "Visual Studio 15 2017" ..
--------------------------------------------------------------------------------------------
###############################################################
To EDIT the QT file and build after
----------------------------------------------------------------------------------------
msbuild QtVTKExample.sln /p:Platform=win32 - this is to build the file after any change
-------------------------------------
################################################################
TO run the executable
----------------------------------------------------------------------------------------------
build\Debug>qtvtkexample.exe  - This is to run the executable 
---------------------------------------------------------------
################################################################

Some fILES have been stored here:
----------------------------------------------------------------------------------------------
C:\Program Files (x86)\VTK\bin - 

C:/Users/ezydhm/Desktop/VTK-8.2.0/VTK-8.2.0 - this is where the source code is (CMake)

C:/Users/ezydhm/Desktop/VTK-8.2.0/VTK-8.2.0/build  - this is where to build the binaries (CMake)
-------------------------------------------------------------------------------------------------

