# setupp

My go-to setup for a C++ project (from [Hanno Hildenbrandt](https://github.com/HHildenbrandt)).

## Build

We use [vcpkg](https://github.com/microsoft/vcpkg) from Microsoft to build on multiple platforms.

### Linux, MacOS

To install CMake:

```bash
sudo apt install cmake		# replace 'apt' with your distro package manager
```

To build the program:

```bash
git clone git@github.com:rscherrer/setupp.git
cd setupp
git submodule add https://github.com/microsoft/vcpkg
git submodule update --init --remote
mkdir build && cd build
cmake ..
cmake --build .
```

The executable `setupp` is built in `../bin/`.

### Windows

[Download](https://github.com/Kitware/CMake/releases/download/v3.23.0/cmake-3.23.0-windows-x86_64.msi) and install CMake. 
Make sure you select the option "Add CMake to the system PATH for the current user" when asked by the installer.

To build the program:

```bash
git clone git@github.com:rscherrer/setupp.git
cd setupp
git submodule add https://github.com/microsoft/vcpkg
git submodule update --init --remote
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

The executable `setupp.exe` is built in `../bin/`.

### IDEs

Many IDEs support CMake out of the box. 'Open folder' should do the trick...
You can use CMake to generate the input files for your favorite IDE too:

```bash
git clone git@github.com:rscherrer/setupp.git
cd setupp
git submodule update --init --recursive
mkdir build
cd build
# Generate VisualStudio project files
cmake -G "Visual Studio 17 2022" -A x64 ..
# Generate Xcode project files (Xcode must be installed)
cmake -G Xcode    
```

This will place the project files in `../build`.
