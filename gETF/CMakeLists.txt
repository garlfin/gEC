include_directories(gETF)

file(GLOB_RECURSE getc_src
        "Struct/*.h"
        "Struct/*.hpp"
        "Struct/*.cpp"
        "Struct/*.c"
        )

add_executable(gETF gETF/main.cpp ${getc_src})