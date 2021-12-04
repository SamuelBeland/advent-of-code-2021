# Advent Of Code 2021

This is my attemp at the [AOC 2021](https://adventofcode.com/2021) !

## Build

This projet uses [CMake 3.16 or higher](https://cmake.org/).

```bash
cd <project-directory>
mkdir build && cd build
# Windows :
cmake ..
cmake --build . --config Release -j 8
# Linux :
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j 8
```

## Running

Run main.exe

## Tests and benchmarks

Run tests.exe

The benchmarks are automatically added to the tests when building in release mode.
