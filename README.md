# setupp

My go-to setup for a C++ project (from [Hanno Hildenbrandt](https://github.com/HHildenbrandt)).

## Prerequisites

* A C++20 compiler
* (optional) [CMake](docs/CMAKE.md) version 3.16 or higher

## Build

Here are instructions to build with CMake, but you can compile the source code with the tools of your choice.

(Click [here](docs/BUILD.md) to build as developer.)

### Linux, MacOS

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

Many IDEs support CMake out of the box. "Open folder" should do the trick...
You can use CMake to generate the input files for your favorite IDE too:

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
