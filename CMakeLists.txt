cmake_minimum_required(VERSION 3.20)

project(learnOpenGLgettingStarted)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DEV_LIBS_ROOT "" CACHE PATH "Folder for external libraries")

if(NOT DEV_LIBS_ROOT)
    message(FATAL_ERROR "Error: Set variable with external libraries folder")
endif()

set(GLFW_DIR   "${DEV_LIBS_ROOT}/GLFW")
set(ASSIMP_DIR "${DEV_LIBS_ROOT}/Assimp")

message(STATUS "DEV_LIBS_ROOT = ${DEV_LIBS_ROOT}")
message(STATUS "GLFW_DIR = ${GLFW_DIR}")
message(STATUS "ASSIMP_DIR = ${ASSIMP_DIR}")

file(GLOB_RECURSE PROJECT_SOURCES
    
    external/glad/*.c
    external/glm/*.cpp
    external/stb_image/*.cpp
    external/imgui-docking/imgui_demo.cpp
    external/imgui-docking/imgui_draw.cpp
    external/imgui-docking/backends/imgui_impl_glfw.cpp
    external/imgui-docking/backends/imgui_impl_opengl3.cpp
    external/imgui-docking/imgui_tables.cpp
    external/imgui-docking/imgui_widgets.cpp
    external/imgui-docking/imgui.cpp

    src/*.cpp
    include/*.cpp
)

add_executable(learnOpenGLgettingStarted
    ${PROJECT_SOURCES}
)

target_include_directories(learnOpenGLgettingStarted PRIVATE
    ${DEV_LIBS_ROOT}/include
    include
    external
    external/imgui-docking
    external/imgui-docking/backends
)

target_link_directories(learnOpenGLgettingStarted PRIVATE
    ${DEV_LIBS_ROOT}/lib/GLFW
    ${DEV_LIBS_ROOT}/lib/assimp
)

target_link_libraries(learnOpenGLgettingStarted PRIVATE
    glfw3.lib
    assimp-vc145-mtd.lib
    opengl32.lib
)

add_custom_command(TARGET learnOpenGLgettingStarted POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${DEV_LIBS_ROOT}/bin/assimp/assimp-vc145-mtd.dll
    $<TARGET_FILE_DIR:learnOpenGLgettingStarted>
)

add_custom_command(TARGET learnOpenGLgettingStarted POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/imgui.ini
    $<TARGET_FILE_DIR:learnOpenGLgettingStarted>
)

add_custom_command(TARGET learnOpenGLgettingStarted POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:learnOpenGLgettingStarted>/assets
)