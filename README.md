[![Build Status](https://travis-ci.com/rdimaio/ModelLoader.svg?token=GZpV6k64pFgseGbhWU1L&branch=master)](https://travis-ci.com/rdimaio/ModelLoader)

# 13CAD - Cross-platform model visualization software

```cpp
// H62PEP - Group 13
```

![Demo Screenshot](/src/gui/icons/screenshot.png?raw=true "Demo Screenshot")

# Key features
- Open, visualize and save .mod and .stl files
- Fully fledged camera controls allow for 
- Modify properties of the visualization, such as the model's opacity or colour
- Toggle the background to be a gradient instead of a uniform colour of your choice
- Switch between different visualization paradigms, such as wireframes and points
- Enable an external light, modifying its intensity and the specularity of the model
- Export volume, surface area, number of cells and vertices as text file data
- Filters, like shrink and clip filters, are available

# Requirements
- Windows/Linux (possibly MAC OSX, not tested)
- CMake 3.3 or greater (if installing from source)
- Qt 5
- VTK 8.2.0

# Installation

## From source
```bash
# Clone the repository
$ git clone https://github.com/rdimaio/ModelLoader

# Go into the ModelLoader folder
$ cd ModelLoader

# Build and make
$ cmake .
$ make

# Run the program
$ ./ModelLoader
```

## Via .zip (Linux)
1. Download the [Linux executable](https://github.com/rdimaio/ModelLoader/releases/tag/1.0.0)
2. Extract and run it

## Via .zip (Windows)
1. Download the [Windows executable](https://github.com/rdimaio/ModelLoader/releases/tag/1.0.0)
2. Extract and run it

## Via the .exe installer (Windows)

Note: the preloaded .mod and .stl test files are not automatically included in the Windows installer.

1. Download the [Windows installer](https://github.com/rdimaio/ModelLoader/releases/tag/1.0.0)
2. Run the installer and choose your installation path.
3. (Optional) Download the [Test models](https://github.com/rdimaio/ModelLoader/releases/tag/1.0.0) to test the program.

## Library structure
The library's structure is a slightly modified version of [this answer](https://stackoverflow.com/a/1398594):

```
/         Makefile and configure scripts.
/bin      Tools build directory
/demos    User-friendly demo programs aimed at providing an interactive understanding of the library elements
/include  Public header files (.h) exposed to the library users
/lib      Library build directory
/src      Source files (.cpp) and private header files (.h)
/src/gui  Graphical user interface files
/tests    Test suites
```

**Public** headers go in ```/include```, while **private** headers go in ```/src```.
[This page](https://stackoverflow.com/questions/2272735/private-public-header-example) illustrates
the difference between the two. In particular:

>Public headers are those needed by the users of the library. 
>Private headers are those needed to compile the library, 
>but which are not needed by library users.

As a general rule, **keep everything private unless absolutely necessary to the user**.

## Coding style

Note: these are not universal coding rules. 
You can write code however you like, but for consistency's sake it's ideal that
all members of the group follow this set of conventions (which are very common in C++).

### Git
- Follow the [Git commit message convention](https://gist.github.com/robertpainsi/b632364184e70900af4ab688decf6f53)
when naming commits. The most important point is that you write your commit messages **in the imperative**: this means
you would say "Fix bug", not "Fixed bug" or "Bug fixes". This is very important, as it's the standard convention
in most (if not all) Git projects you will be part of.
```bash
# Good commit name
git commit -m "Add getVolume() function to vector.cpp"

# Bad commit name
git commit -m "Updated vector.cpp"
```

### C++
- Class names must be capitalised (e.g. ```class Vector```, ```class Shape```)
- Functions and variables follow the ```camelCase``` naming convention (e.g. ```getVolume()```, ```sampleVariable```. 
See [this](https://en.wikipedia.org/wiki/Camel_case) for more details.)
- Use include guards in header files (like ```#ifndef```) instead of ```#pragma once```.
The latter is not in the C++ standard, and might not be supported by some compilers;
our goal is portability, so it's better if we stick to the standard.
Refer to the existing header files to make sure that you understand what an include guard is.
- Always try to comment **above** the block of code you're commenting, not to the side.
Side comments are okay if you're just explaining something specific about that line of code.
- For multi-line comments, use /* */. For single-line comments, use //.
- The opening curly brace of a function/class/etc. must go on the **same line** as the function/etc. e.g.:
```cpp
// Good
void main() {
    // code
}

// Not so good
void main()
{
    // code
}
```
The rationale behind this is that less vertical space is taken by the first convention.

# Documentation
Documentation is essential to an easily maintanable project, as it
is our "user-friendly" interface for eventual users (and for collaborators) 
of the library (the alternative would be having to navigate 
through dozens of source files and reading comments).
We are going to use **Doxygen** to automate our documentation.

The documentation for our project can be found [here](https://rdimaio.github.io/ModelLoader/html/).

## Doxygen
[Doxygen](http://www.doxygen.org/) is a tool that generates documentation from
the comments in source code. There are several ways to mark a comment so that
Doxygen extracts it to docs; for consistency's sake, 
we are going to use ```/** .. */``` (note the double asterisk on
the beginning line) **above** what we're documenting, e.g.:
```cpp
/**
 * Computes the cross product of two vectors.
 */
Vector3D cross(Vector3D rhsVector);
```
Note that ```/** .. */``` can also be used for single-line comments to the
right of a line of code and that those will also be picked up by Doxygen, 
but they will only mark the line they're on (instead of what's below them).

# Continuous Integration (CI) and testing
Continuous Integration (CI) is an extremely useful tool that automatically
executes the tests you've written every time you push a commit to the GitHub repository.
This allows us to be immediately notified in case our newest commit breaks the library's
tested functionalities. Our tools to achieve this are **Google Test** and **Travis CI**.

## Google Test
[Google Test](https://github.com/google/googletest) is an intuitive testing tool
which (unlike ```ctest```) allows us to have multiple tests per file 
(more efficient and organised). Each test is tagged with a name, helping us debug
the library in case one of the tests fails.
You can read the [primer](https://github.com/google/googletest/blob/master/googletest/docs/primer.md)
for an overview of the possible commands or simply refer to the existing test files.

### Testing on your PC
If you want to run the tests yourself, execute these commands:
```bash
cd ModelLoader
cmake -DTESTING=ON .
make
./Test_ModelLoader
```

## Travis CI
[Travis CI](https://travis-ci.com/) is a hosted CI tool that can be configured via
the ```.travis.yml``` file. Whenever a commit is pushed to the repository, Travis
runs the ```.travis.yml``` configuration on a hosted environment (generally
a virtual machine running Linux, specifically Ubuntu) and sends you an email 
in case the latest commit breaks the tests in any way.

# Possible future implementations
- Code could be cleaned up, especially in mainwindow.cpp.
The different functions could be put in different files,
improving the ease of navigating the GUI source code.
- Many class member variables could be transformed into static/constant variables;
[This link](https://stackoverflow.com/questions/5620256/understanding-how-to-correctly-treat-c-class-constants)
provides a good understanding of the matter.
- A function to export a depth map could be added, using [this example](https://vtk.org/Wiki/VTK/Examples/Cxx/Utilities/ZBuffer)
as a starting point.
- Colorblind mode could be implemented.

# Useful links

- [An excellent and very brief git guide](http://rogerdudler.github.io/git-guide/)
- [A working example of Qt and VTK working together.](https://vtk.org/Wiki/VTK/Examples/Cxx/Qt/SideBySideRenderWindowsQt)
It's very useful to check if everything is installed correctly; just follow
the instructions at the end of the page to build and run it.
