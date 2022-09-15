cmake_minimum_required(VERSION 3.22)
project(iME)

set(CMAKE_CXX_STANDARD 23)
include_directories(Vendor)
include_directories(Engine)

set(CMAKE_CXX_FLAGS "-static")

file(GLOB_RECURSE ime_src
        "Engine/*.h"
        "Engine/*.hpp"
        "Engine/*.cpp"
        "Engine/*.c"
        )

add_executable(iME main.cpp ${ime_src} Engine/Struct/ObjectData.h Engine/Component/Components/Camera.cpp Engine/Component/Components/Camera.h Engine/Component/Managers/CameraManager.h)

find_library(LIBGLFW glfw3 Vendor/glfw)
target_link_libraries(iME ${LIBGLFW})
