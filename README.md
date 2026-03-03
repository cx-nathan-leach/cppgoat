# C++ Goat
An intentionally vulnerable web application with the backend written in C++.


## Issue Validation Rubric

This is a rubric of what types of vulnerabilities intentionally implemented.  It is intended
to be terse and vauge so that AI code scanners can't read this file and report the results.
The AI needs to demonstrate it recognizes the vulnerabilities without the assistance of
developer commentary.


## Building

This currently targets Linux only. The build environment requires:

* gcc
* gdb
* cmake
* conan

Python and Pip are useful for installing Conan.


### Building Debug

```bash
conan install . -s build_type=Debug --build=missing
cmake --preset=conan-debug
cmake --build --preset=conan-debug
```

### Building Release

```bash
conan install . -s build_type=Release --build=missing
cmake --preset=conan-release
cmake --build --preset=conan-release
```