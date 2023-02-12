Set-up for the [Peregrine](https://www.rug.nl/society-business/centre-for-information-technology/research/services/hpc/facilities/peregrine-hpc-cluster?lang=en) cluster

Load necessary modules:

```bash
module load CMake
module load binutils
module load git
```

Build the program:

```bash
git clone git@github.com:rscherrer/setupp.git
cd setupp
git submodule update --init --remote
mkdir build && cd build
cmake ..
cmake --build .
```

The executable `setupp` is built in `../bin/`.
Make sure that the loaded version of CMake is adequate with respect to the version required in `CMakeLists.txt`. 
Explore available versions with `module spider CMake` and replace `CMake` in `module load CMake` by the version required, if any error occurs (you can also change the required version in `CMakeLists.txt`).
