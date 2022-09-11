#include "Engine/Windowing/Window.h"
#include <iostream>

int main()
{
    try {
        Window window(glm::vec2(1280, 720), "iME");
        window.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
}
