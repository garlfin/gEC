cmake_minimum_required(VERSION 3.23)
project(iME)

set(CMAKE_CXX_STANDARD 23)
include_directories(Engine/Vendor)


set(CMAKE_CXX_FLAGS "-static")
add_executable(iME main.cpp Engine/glad.c Engine/Windowing/Window.h Engine/Windowing/Window.cpp Engine/Asset/Asset.h Engine/Asset/AssetManager.h Engine/Asset/GLBuffer.h Engine/Asset/Mesh/VAO.h Engine/Asset/Mesh/VAO.cpp Engine/Asset/Material/SubShader.cpp Engine/Asset/Material/SubShader.h Engine/Asset/Material/Shader.cpp Engine/Asset/Material/Shader.h)

find_library(LIBGLFW glfw3 Engine/Vendor/glfw)
target_link_libraries(iME ${LIBGLFW})