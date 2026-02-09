# setupp: Minimal, modular, cross-platform C++ project configuration

This repository contains a minimal example of my go-to setup for C++ projects (mostly individual-based evolutionary simulations). 

![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Tests](https://img.shields.io/badge/tests-passing-brightgreen)
![Coverage](https://img.shields.io/badge/coverage-100%25-brightgreen)

## Description

The setup ships with [CMake](https://cmake.org) configuration files designed to build across platforms (assuming no platform-specific library or code is being used). The architecture supports testing, coverage analysis, memory checks and profiling out of the box, with helper bash scripts to easily switch between these different configurations.

## How to

In this guide we show how to build the program using the [CMake](https://cmake.org/) build system. Below we provide a ready-made CMake configuration file but the user is free to use any custom configuration.

### Prerequisites

- Any modern C++ compiler (e.g. [g++](https://gcc.gnu.org/), [Clang](https://clang.llvm.org/) or [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/))
- Build system: [CMake](https://cmake.org/) (>= 3.16)
- Source retrieval: [git](https://git-scm.com/) (optional)

### Download the code

You can download the source code using `git`:

```shell
git clone https://github.com/rscherrer/setupp
```

Make sure you run the following commands from within the root directory of the repo by using:

```bash
cd setupp
```

### Configure CMake

Our setup uses the following `CMakeLists.txt` configuration file, which you can also find [here](./dev/cmake/release.cmake). Make sure to have it saved in the root directory of the repository.

```cmake
# CMakeLists.txt

# CMake
cmake_minimum_required(VERSION 3.16)

# Project name
project(setupp)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boilerplate
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# Release mode
set(CMAKE_BUILD_TYPE "Release")

# Source code
add_subdirectory(src)
```

Then, make sure to have this other `CMakeLists.txt` file, this time saved in the `src/` folder. Normally, it should already be present in the right folder if you downloaded this repository.

```cmake
# src/CMakeLists.txt

# Collect source and header files
file(GLOB_RECURSE src 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

# Instruct CMake to build the binary
add_executable(setupp "${CMAKE_SOURCE_DIR}/main.cpp" ${src})

# Place the binary into ./bin/
set_target_properties(setupp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<0:>)
```

### Build the program

Then, run the following code from within the repository to create a build folder and instruct CMake to build the program in release mode according to the instructions given in the `CMakeLists.txt` configuration file.

```shell 
cmake -S . -B build
cd build
cmake --build .
```

This setup places the compiled executable in the `bin/` folder.

Note that the steps are **the same on Windows, MacOS and Linux**, although the installation steps of a suitable C++ compiler will typically differ from platform to platform (e.g. environment variables on Windows), and so we refer the reader to online documentation for that.

### IDEs

Many IDEs such as [Visual Studio](https://visualstudio.microsoft.com/) or [XCode](https://developer.apple.com/xcode/) support CMake out of the box. "Open folder" should do the trick...

You can use CMake to generate the input files for your favorite IDE too. For example, running the following from within the recently created `build/` folder will generate Visual Studio project files:

```shell
cmake -G "Visual Studio 17 2022" -A x64 ..
```

For XCode, run:

```shell
cmake -G Xcode    
```

This will place the project files in `build/`.

### Usage

To run the compiled program, go to `bin/` and:

```shell
./setupp
```

or whatever the program is called.

### Note

The script `build.sh` can be used to build the program. It is located in the `dev/` folder and should work fine on a Unix-like system. See [here](./dev/README.md) for more details.

## Tests

This program is set up to be tested using the [Boost.Test](https://www.boost.org/doc/libs/1_85_0/libs/test/doc/html/index.html) library. All the tests should be placed in the `tests/` folder. Below we show how to modify our main setup (explained above) in order to run the tests as separate executables that can be used to check the proper behavior of the program. Check out [this page](https://en.wikipedia.org/wiki/Test-driven_development) for more information about **_unit testing_** and **_test-driven development_** (TDD).

### Prerequisites

- Any modern C++ compiler (e.g. [GCC](https://gcc.gnu.org/), [Clang](https://clang.llvm.org/) or [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/))
- Build system: [CMake](https://cmake.org/) (>= 3.16)
- Source retrieval: [git](https://git-scm.com/)

([Boost.Test](https://www.boost.org/doc/libs/1_86_0/libs/test/doc/html/index.html) and [vcpkg](https://vcpkg.io/) will be downloaded in the process.)

### Download the code 

First, download the repository and set it as working directory if you have not already done so:

```shell
git clone https://github.com/rscherrer/setupp
cd setupp
```

### Configure CMake

Make sure to save the following as a `CMakeLists.txt` file located in the root of the repository. This file is also available [here](./dev/cmake/tests.cmake).

```cmake
# CMakeLists.txt

# CMake
cmake_minimum_required(VERSION 3.16)

# Set up vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
if (WIN32)
    set(VCPKG_TARGET_TRIPLET x64-windows)
endif()

# Project name
project(setupp)

# Git will be needed to install Boost
find_package(Git REQUIRED)
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --remote
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
if (NOT GIT_SUBMOD_RESULT EQUAL "0")
    message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
endif()

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boilerplate
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# Debug mode
set(CMAKE_BUILD_TYPE "Debug")

# Source code
add_subdirectory(src)
add_subdirectory(tests)
```

This file is substantially longer than the one used in our main (release) setup, as it now contains all the build information needed to download the necessary tools from the [Boost](https://www.boost.org/) library for unit tests, and compile those tests using CMake. 

Note that the source code for the tests is located in `tests/`.

On top of that file, make sure to have the following `CMakeLists.txt` file saved in the `src/` directory (it is the same one as in our main setup):

```cmake
# src/CMakeLists.txt

# Collect source and header files
file(GLOB_RECURSE src 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

# Instruct CMake to build the binary
add_executable(setupp "${CMAKE_SOURCE_DIR}/main.cpp" ${src})

# Place the binary into ./bin/
set_target_properties(setupp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<0:>)
```

Finally, make sure that the following `CMakeLists.txt` file is saved in the `tests/` directory (this file should be already provided in the right folder within this repository):

```cmake
# tests/CMakeLists.txt

# Find Boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Model 'unit' files
file(GLOB_RECURSE unit ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Include test utilities
include_directories(${CMAKE_SOURCE_DIR}/tests)

# Automatically find all test files ending with *tests.cpp in the tests directory
file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*tests.cpp)

# Build each executable
foreach(TEST_SOURCE IN LISTS TEST_SOURCES)
    # Extract the name of the test executable from the filename
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    # Create the test executable
    add_executable(${TEST_NAME} ${TEST_SOURCE} ${unit} ${CMAKE_SOURCE_DIR}/tests/testutils.cpp)
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/tests)
    target_link_libraries(${TEST_NAME} PUBLIC Boost::unit_test_framework)
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/tests/$<0:>)
endforeach()
```

### Install Boost

Run the following from within the root of the repo to install the testing framework through `git`:

```shell
git submodule add --force https://github.com/microsoft/vcpkg
git submodule update --init --remote
```

These steps will connect the repo to Microsoft's [vcpkg](https://vcpkg.io/) installer, whose job will be to download the required elements from [Boost](https://www.boost.org/) necessary for unit testing (instructions for that are given in the file `vcpkg.json` provided with this repo). 

This setup has the advantage of integrating with CMake and working well across platforms, so the steps are **the same on Windows, Linux or MacOS**. However, in case errors occur during this installation process, we recommend to refer to the log files created by `vcpkg` (some dependencies may be missing and they will be listed there if that is the case).

### Build the tests

Then, run:

```shell
cmake -S . -B build
cd build
cmake --build .
```

Here, the `cmake` command downloads the necessary dependencies through `vcpkg`, and builds all the targets (in debug mode) required by the `CMakeLists.txt` configuration --- not just the program itself, but also the tests, whose executables can be found in `bin/tests/`.

### Run the tests

Simply run those executables to run the tests. For example:

```shell
cd bin/tests
./tests
```

or whichever other test executable may have been created.

### Note

The `build.sh` script from the `dev/` folder was used during development to build the tests, followed by `run_tests.sh`, still in `dev/`. They should work fine on a Unix-like system. See [here](./dev/README.md) for more details.

## Example workflow (Unix)

This repository comes with a series of handy bash scripts, located in the `dev/` folder, which may be used to navigate between the steps explained above. Specifically, this folder contains different template `CMakeLists.txt` configuration files, and the user may switch among them by running:

```shell
./dev/switch.sh --<config>
```

from the root of the repository, where `<config>` can be either of: `release`, `tests`, `coverage`, or `profile`. After switching configuration, the script `dev/build.sh` may be used to re-compile the entire project:

```shell
./dev/build.sh
```

Once the project has been re-built in the right configuration, helper scripts can be used to run development and analysis tools on the compiled program. For example:

```shell
./dev/switch.sh --tests
./dev/build.sh
./dev/run_tests.sh
```

will run all the test executables found in `bin/tests/` and tell the user whether a test is failing. 

To quantify code coverage, use:

```shell
./dev/switch.sh --coverage
./dev/build.sh
./dev/run_lcov.sh
```

This will run [LCOV](https://github.com/linux-test-project/lcov) on all the tests and save its output in a folder named `lcov/`. Simply open `lcov/index.html` in a browser to interactively view which lines of code are covered and which are not. 

For memory use (e.g. memory leaks, memory access errors or bytes not freed), the following commands:

```shell
./dev/switch.sh --tests
./dev/build.sh
./dev/run_valgrind.sh
```

will run [Valgrind](https://valgrind.org/)'s Memcheck tool on test executables, return a summary of errors to the screen, and save its output in a folder called `valgrind/`.

To profile the code, use:

```shell
./dev/switch.sh --profile
./dev/build.sh
./dev/run_gprof.sh
```

This will use GNU's [gprof](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_mono/gprof.html) tool to identify speed bottlenecks. The output will be saved in a folder named `gprof/`.

Finally, once all checks and balances pass, the program may be compiled in release mode:

```shell
./dev/switch.sh --release
./dev/build.sh
```

Note that the third-party programs used by these development helper scripts (LCOV, Valgrind, gprof) must be installed on your machine for the above to work. Also note that these helper scripts are designed **for Unix systems**. For other platforms, debug (tests) and release configurations as explained in the previous sections should work. For code coverage, memory checks and profiling, you will need to find your own platform-specific tools.

## About

This code is written in C++20. The project was developed, built and tested on Ubuntu Linux 24.04 LTS, using [Visual Studio Code](https://code.visualstudio.com/) 1.108.0 ([C/C++ Extension Pack](https://marketplace.visualstudio.com/items/?itemName=ms-vscode.cpptools-extension-pack) 1.3.1). [CMake](https://cmake.org/) 3.28.3 was used as build system, with [g++](https://gcc.gnu.org/) 13.3.0 as compiler. [GDB](https://www.gnu.org/savannah-checkouts/gnu/gdb/index.html) 15.0.50.20240403 was used for debugging. Tests (see [here](doc/TESTS.md)) were written with [Boost.Test](https://www.boost.org/doc/libs/1_85_0/libs/test/doc/html/index.html) 1.90.0, itself retrieved with [Git](https://git-scm.com/) 2.43.0 and [vcpkg](https://github.com/microsoft/vcpkg) 2025.04.09. Memory use was checked with [Valgrind](https://valgrind.org/) 3.22.0. Code coverage was analyzed with [LCOV](https://github.com/linux-test-project/lcov) 2.0-1. Profiling was performed with [gprof](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_mono/gprof.html) 2.42. (See the `dev/` folder and [this page](dev/README.md) for details about the checks performed.) During development, occasional use was also made of [ChatGPT](https://chatgpt.com/) and [GitHub Copilot](https://github.com/features/copilot).

## Links

This setup has been used, in this form or slightly modified, in the following (non-exhaustive) list of projects:

* [binprint](https://github.com/rscherrer/binprint): C++ library to save binary output data files
* [brachypode](https://github.com/rscherrer/brachypode): simulation of adaptation to a changing climate in a facilitated species
* [porpgame](https://github.com/rscherrer/porpgame): simulation of a board game in preparation
* [readpars](https://github.com/rscherrer/readpars): C++ library to read parameter text files
* [reschoice](https://github.com/rscherrer/reschoice): evolutionary simulation of ecological specialization with resource choice
* [speciome](https://github.com/rscherrer/speciome): evolutionary simulation of speciation with gene networks

## Permissions

Copyright (c) 2025-2026, Raphaël Scherrer. 

This setup was inspired by Hanno Hildenbrandt and Richèl Bilderbeek. This code is licensed under the MIT license. See [license file](LICENSE.txt) for details.