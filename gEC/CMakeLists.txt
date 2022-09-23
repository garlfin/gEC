include_directories(Vendor)
include_directories(gEC/Engine)

file(GLOB_RECURSE ime_src
        "gEC/Engine/*.h"
        "gEC/Engine/*.hpp"
        "gEC/Engine/*.cpp"
        "gEC/Engine/*.c"
        )

add_executable(gEC gEC/main.cpp ${ime_src})

find_library(LIBGLFW glfw3 Vendor/glfw)
target_link_libraries(gEC ${LIBGLFW})
