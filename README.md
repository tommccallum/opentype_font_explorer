# OpenType library

Writing a OpenType Font reader for fun.  Very early stages, may not finish.

## Directory Layout

* build - output from build process
* cmake - additional files required for build/test process
* executables - applications to run mainly to test library
* fonts - example TTF files for reading
* include - header files for installation
* install - local install directory for testing installation
* src - CPP code files for library
* tests - Catch2 tests for library

## How to build and run?

`build$ cmake ..`
`build$ make`
Run testsuite:
`build$ make tests`
To test using valgrind use the following command:
`build$ ctest -T memcheck`
