# setupp

My go-to setup for a C++ project (after [Hanno Hildenbrandt](https://github.com/HHildenbrandt) and [Richel Bilderbeek](https://github.com/richelbilderbeek)). It has two important features:
* It uses [CMake](https://cmake.org) to be able to build on multiple platforms
* It comes into two flavors, **user** and **developer**. The user-configuration does the minimum to give the user a working program. The developer-configuration also builds all the tests and downloads (with [vcpkg](https://github.com/rscherrer/vcpkg)) the necessary libraries (here [Boost.Test](https://github.com/boostorg/test)) to do so.

## About

This setup is intended for biologists who need C++ in their research (e.g. for simulation studies or fast implementations of some analytical pipelines). It is made to build command-line interface programs and does not use anything fancy like GPUs. As such, it is pretty basic, but it does the job for many straightforward applications. You can use this setup for your own program by simply downloading it and tweaking it to suit your needs. You may get rid of `README.md` and the `doc/` folder, which only contain documentation for this repository, and write your own documentation instead.

**Important:** you will need to replace `setupp` with the name of your project wherever needed (most importantly in `CMakeLists.txt` but also in `vcpkg.json` if you use the developer build configuration, see below).

## Prerequisites

* A C++20 compiler (e.g. [GCC](https://gcc.gnu.org) or [Clang](https://clang.llvm.org))
* CMake version 3.16 or higher (click [here](doc/CMAKE.md) for how to install)

## Build

The following shows how to download this repository and build the program `setupp` according to the **user** configuration on different platforms. This should be the most common one or at least the one used by the end user who wishes to compile this code. It compiles the code in release mode with some optimization flags. However, during software development the developer may require a testing framework or to build in debug mode, which is much slower. For this there is the **developer** configuration, which downloads and installs the testing library `Boost.Test` via `vcpkg` (follow instructions [here](doc/BUILD.md) for that).

If you do not need the developer configuration at all, you may set `CMakeLists.txt` as `CMakeLists_user.txt` and get rid of `CMakeLists_devel.txt`, `CMakeLists_user.txt`, `tests/` and `vcpkg.json`.

If you just want an ultra-basic **user** version of this setup check this [page](https://github.com/rscherrer/setupp-basic).

All of the build details should be saved in the `./build/` folder during the building process.

(Click [here](doc/BUILD.md) to build as **developer**.)

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

### High Performance Computing Cluster

(Click [here](doc/PEREGRINE.md) to build on the [Peregrine](https://www.rug.nl/society-business/centre-for-information-technology/research/services/hpc/facilities/peregrine-hpc-cluster?lang=en) cluster --- replaced by Habrok in 2023.)

(Click [here](doc/HABROK.md) to build on the [Habrok](https://www.rug.nl/society-business/centre-for-information-technology/research/services/hpc/facilities/peregrine-hpc-cluster?lang=en) cluster.)

### IDEs

Many IDEs such as VisualStudio or XCode support CMake out of the box. "Open folder" should do the trick...
You can use CMake to generate the input files for your favorite IDE too (here a MacOS example):

```shell
git clone git@github.com:rscherrer/setupp.git
cd setupp
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

## Projects using this setup

* [speciome](https://github.com/rscherrer/speciome)
* [brachypode](https://github.com/rscherrer/brachypode)
* [reschoice](https://github.com/rscherrer/reschoice)
* [hemigene](https://github.com/rscherrer/hemigene)
