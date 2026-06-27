# SG Engine

A personal graphics engine developed as a learning project.

Built with OpenGL 3.3 and featuring a graphical editor powered by Dear ImGui.

## Goals

The purpose of this project is to gain hands-on experience with graphics programming, rendering techniques, engine architecture, and modern C++ development. It is not intended to compete with existing game engines, but to serve as a playground for implementing graphics concepts from scratch.

## Libraries

* [Glad](https://glad.dav1d.de/)
* [Glfw](https://www.glfw.org/) (3.4.0)
* [Glm](https://github.com/g-truc/glm)
* [Json](https://github.com/nlohmann/json)
* [Stb](https://github.com/nothings/stb/blob/master/stb_image.h)
* [Dear ImGui](https://github.com/ocornut/imgui)
* [Assimp](https://github.com/assimp/assimp) (6.0.4)

## How to build

### Requirements

- CMake 3.2
- C++20 compiler
- OpenGL 3.3
  
### Build

1. Install [CMake](https://cmake.org/).
2. Download precompiled builds of GLFW and Assimp, or build them yourself.
3. Set Cmake variable `DEV_LIBS_ROOT` to the libraries root folder.
   
   The expected folder structure is this:
   ```
   yourfolder
    - bin (dll)
      - assimp
    - include
      - assimp
      - GLFW
    - lib/
      - assimp
      - GLFW
   ```
4. Configure and build