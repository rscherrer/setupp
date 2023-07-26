# setupp

My go-to setup for a C++ project (after [Hanno Hildenbrandt](https://github.com/HHildenbrandt) and [Richel Bilderbeek](https://github.com/richelbilderbeek)). It has two important features:
* It uses [CMake](https://cmake.org) to be able to build on multiple platforms
* It comes into two flavors, **user** and **developer**. The user-configuration does the minimum to give the user a working program. The developer-configuration also builds all the tests and downloads (with [vcpkg](https://github.com/rscherrer/vcpkg)) the necessary libraries (here [Boost.Test](https://github.com/boostorg/test)) to do so.

## Prerequisites

* A C++20 compiler (e.g. [GCC](https://gcc.gnu.org) or [Clang](https://clang.llvm.org))
* CMake version 3.16 or higher (click [here](docs/CMAKE.md) for how to install)

## Build

Here are instructions to build with CMake, but you can compile the source code with the tools of your choice. Here we are building as **user**. All of the build details should be saved in the `./build/` folder during the building process.

(Click [here](docs/BUILD.md) to build as **developer**.)

(Click [here](docs/PEREGRINE.md) to build on the [Peregrine](https://www.rug.nl/society-business/centre-for-information-technology/research/services/hpc/facilities/peregrine-hpc-cluster?lang=en) cluster.)

### Linux, MacOS

In the terminal:

```shell
git clone git@github.com:rscherrer/setupp.git
cd setupp
cp CMakeLists_user.txt CMakeLists.txt # user configuration
mkdir build && cd build
cmake ..
cmake --build .
```

The executable `setupp` is built in `../bin/`.

### Windows

In the command prompt:

```cmd
git clone git@github.com:rscherrer/setupp.git
cd setupp
copy CMakeLists_user.txt CMakeLists.txt :: user configuration
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

The executable `setupp.exe` is built in `../bin/`.

### IDEs

Many IDEs such as VisualStudio or XCode support CMake out of the box. "Open folder" should do the trick...
You can use CMake to generate the input files for your favorite IDE too (here a MacOS example):

```shell
git clone git@github.com:rscherrer/setupp.git
cd speciom
cp CMakeLists_user.txt CMakeLists.txt # user configuration
mkdir build
cd build
# Generate VisualStudio project files
cmake -G "Visual Studio 17 2022" -A x64 ..
# Generate Xcode project files (Xcode must be installed)
cmake -G Xcode    
```

This will place the project files in `../build`.

## Note

In all the examples above you will notice that we specify:

```shell
cp CMakeLists_user.txt CMakeLists.txt
```

This is to make sure to build the fast, optimized, release version of the program. This is important as the developer (debug) version is not optimized and requires extra libraries to run all the tests, so it should not be used by the user.
