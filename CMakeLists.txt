cmake_minimum_required(VERSION 3.22)
project(iME)

set(CMAKE_CXX_STANDARD 23)
include_directories(Engine/Vendor)


set(CMAKE_CXX_FLAGS "-static")
add_executable(iME main.cpp Engine/glad.c Engine/Windowing/Window.h Engine/Windowing/Window.cpp Engine/Asset/Asset.h Engine/Asset/GLBuffer.h Engine/Asset/Mesh/VAO.h Engine/Asset/Mesh/VAO.cpp Engine/Asset/Material/SubShader.cpp Engine/Asset/Material/SubShader.h Engine/Asset/Material/Shader.cpp Engine/Asset/Material/Shader.h Engine/Struct/CameraData.h Engine/Asset/Texture/Texture.cpp Engine/Asset/Texture/Texture.h Engine/Asset/Texture/Texture2D.cpp Engine/Asset/Texture/Texture2D.h Engine/Struct/PVRHeader.h Engine/Component/Entity.cpp Engine/Component/Entity.h Engine/Asset/AssetManager.h Engine/Component/Component.cpp Engine/Component/Component.h Engine/Component/ComponentManager.h Engine/Component/MeshRenderer.cpp Engine/Component/MeshRenderer.h)

find_library(LIBGLFW glfw3 Engine/Vendor/glfw)
target_link_libraries(iME ${LIBGLFW})
