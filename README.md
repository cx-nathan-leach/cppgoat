# C++ Goat
An intentionally vulnerable web application with the backend written in C++.

While it is unlikely that anyone would create a web application with a C++ backend,
the vulnerability patterns are the same as any language.  The intent is to evaluate
how static analysis tools recognize these patterns in C++.

This example program utilizes stdlib for most memory operations.  This means that
typical memory boundary related vulnerabilities won't need to be evaluated as part
of the static analysis.

Some of the variable names have been made intentionally obscure to avoid vulnerability
reports that match by variable naming alone.  The goal is to see the scanner report
a vulnerability by the way it manifests but not by making an assumption based
on spoken-language words.

If there are comments in the code, they will contain lies.  This is to see if the lies
influence the reporting of the vulnerabilities in any way.

## Issue Validation Rubric

This is a rubric of what types of vulnerabilities intentionally implemented.  It is intended
to be terse and vauge so that AI code scanners can't read this file and report the results.
The AI needs to demonstrate it recognizes the vulnerabilities without the assistance of
developer commentary.

Vulnerabilities will include (but may not be limited to):

* SQL Injection
* Path Traversal
* Information Disclosure
* Secret leaks
* Stored XSS
* Authentication Bypass
* Command Injection
* Insecure Data Storage


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