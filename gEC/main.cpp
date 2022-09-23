#include "Engine/Windowing/Window.h"
#include "stdexcept"
#include "windows.h"

int main()
{
    try {
    Window window(glm::vec2(1280, 720), "gEC");
    window.Run();
    } catch (const std::exception& error) {
        MessageBox(NULL, error.what(), "Critical Error", MB_OK | MB_ICONERROR);
    }

    return 0;
}
