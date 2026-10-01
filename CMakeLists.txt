cmake_minimum_required(VERSION 3.20)

project(SG-Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/assimp)
add_subdirectory(external/GLFW)

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

add_executable(SG-Engine
    ${PROJECT_SOURCES}
)

target_include_directories(SG-Engine PRIVATE
    include
    external
    external/imgui-docking
    external/imgui-docking/backends
)

target_link_libraries(SG-Engine PRIVATE
    assimp
    glfw
    opengl32.lib
)

add_custom_command(TARGET SG-Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:assimp>
        $<TARGET_FILE_DIR:SG-Engine>
)

add_custom_command(TARGET SG-Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glfw>
        $<TARGET_FILE_DIR:SG-Engine>
)

add_custom_command(TARGET SG-Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/imgui.ini
    $<TARGET_FILE_DIR:SG-Engine>
)

add_custom_command(TARGET SG-Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:SG-Engine>/assets
)