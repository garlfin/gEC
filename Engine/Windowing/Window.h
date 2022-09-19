//
// Created by scion on 8/29/2022.
//

#ifndef IME_WINDOW_H
#define IME_WINDOW_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/vec2.hpp>
#include <string>
#include "../Asset/GLBuffer.h"
#include "Component/Managers/CameraManager.h"


class Window {
protected:
    GLFWwindow* window;
public:
    glm::i16vec2 Size;

    glm::i16vec2 MousePosition;
    glm::vec2 MouseNormalized() { return MousePosition / Size; }

    const float Aspect();
    const char* const Title;

    CameraManager* CamManager;

    Window(glm::i16vec2, const char*);
    // Window(uint16_t, uint16_t, std::string);
    // Window(glm::i16vec2, const char*);

    void Run();
};


#endif //IME_WINDOW_H
