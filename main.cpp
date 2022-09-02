#include "Engine/Windowing/Window.h"

int main()
{
    Window window(glm::vec2(1280, 720), "iME");
    window.Run();

    return 0;
}
