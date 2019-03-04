[![Build Status](https://travis-ci.com/rdimaio/ModelLoader.svg?token=GZpV6k64pFgseGbhWU1L&branch=master)](https://travis-ci.com/rdimaio/ModelLoader)

# Cross-platform model loading library

```cpp
// H62PEP - Group 13
```

## TODOs
- Fix indentation in GitHub being different from how it should be
- Where I left off: test_model.cpp, implementing parseCellTest. Maybe
I should change the way cell behaves, because right now it's holding the entire material,
but maybe it doesn't need it.
- Move main from src to src/gui in case something fails (might work better there)
- Add IDs to all classes; right now, saving is not really feasible.
Might need to change the way vector ID is saved in saveToFile in model.
- Implement the things at the end of worksheet 6
- Maybe change vectors so that they hold their IDs too (might be important for cells,
as right now in model.cpp the vertices' coordinates are assigned and the vertices IDs
are lost when not looking at it from the model's perspective.
- Maybe change all floats to doubles
- Maybe change all parameters so that they are received by reference
- Maybe typedef an array of vector3D like:
```typedef std::vector<int> int_vec_t;``` source:  https://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htmhttps://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htm

### Cell
- Maybe add static const ints that hold the number of verteces of each shape in cell.h
like this: https://stackoverflow.com/questions/5620256/understanding-how-to-correctly-treat-c-class-constants

### Model
- Do something about the \r that gets read when parsing; make it so that the
parser ignores that altogether
- Maybe make it so that the save feature checks whether the input model file is
still present; if it isn't, instead of copying from it, it goes through the
loaded points and parses them to the output file
- Make it so that an empty cell/material/model is stored in new vector positions when the vector is resized

## Library structure
The library's structure is a slightly modified version of [this answer](https://stackoverflow.com/a/1398594):

```
/         Makefile and configure scripts.
/bin      Tools build directory
/demos    User-friendly demo programs aimed at providing an interactive understanding of the library elements
/include  Public header files (.h) exposed to the library users
/lib      Library build directory
/src      Source files (.cpp) and private header files (.h)
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

# Useful info

- A cell is a shape (e.g. tetrahedron)

## Useful links

- [An excellent and very brief git guide](http://rogerdudler.github.io/git-guide/)
- [A working example of Qt and VTK working together.](https://vtk.org/Wiki/VTK/Examples/Cxx/Qt/SideBySideRenderWindowsQt)
It's very useful to check if everything is installed correctly; just follow
the instructions at the end of the page to build and run it.
