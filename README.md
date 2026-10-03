# SG Engine

A personal graphics engine developed as a learning project.

Built with OpenGL 3.3 and featuring a graphical editor powered by Dear ImGui.

## Goals

The purpose of this project is to gain hands-on experience with graphics programming, rendering techniques, engine architecture, and modern C++ development. It is not intended to compete with existing game engines, but to serve as a playground for implementing graphics concepts from scratch.

## Libraries

* [Glad](https://glad.dav1d.de/)
* [Glfw](https://github.com/glfw/glfw)
* [Glm](https://github.com/g-truc/glm)
* [Json](https://github.com/nlohmann/json)
* [Stb](https://github.com/nothings/stb/blob/master/stb_image.h)
* [Dear ImGui](https://github.com/ocornut/imgui)
* [Assimp](https://github.com/assimp/assimp)

## How to build

The project has been tested with Clang/Clang++ using CMake and Ninja.

### Requirements

- [CMake](https://cmake.org/) 3.2+
- [Ninja](https://ninja-build.org/) 
- [Clang/Clang++](https://github.com/llvm/llvm-project)
- OpenGL 3.3
  
### Configure & Build

Inside root folder:
```bash
cmake -S . -B build -G Ninja DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
```
```bash
cmake --build build
```