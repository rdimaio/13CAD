# Cross-platform model loading library

```cpp
// H62PEP - Group 13
```

## Library structure
The library's structure is a slightly modified version of [this answer](https://stackoverflow.com/a/1398594):

```
/         Makefile and configure scripts.
/src      Source files (.cpp) and private header files (.h)
/include  Public header files (.h) exposed to the library users
/lib      Library build directory
/bin      Tools build directory
/tests     Test suites that should be run during a `make test`
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

## Useful info

- A cell is a shape (e.g. tetrahedron)

## Useful links

- [An excellent and very brief git guide](http://rogerdudler.github.io/git-guide/)
