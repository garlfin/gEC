//
// Created by scion on 8/29/2022.
//

#ifndef IME_WINDOW_H
#define IME_WINDOW_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/vec2.hpp>
#include <string>
#include "../Asset/AssetManager.h"
#include "../Asset/GLBuffer.h"


class Window {
protected:
    GLFWwindow* window;
public:
    AssetManager<GLBuffer<float>> TextManager;
    glm::i16vec2 Size;
    std::string Title;

    Window(glm::i16vec2, std::string const&);
    // Window(uint16_t, uint16_t, std::string);
    // Window(glm::i16vec2, const char*);

    void Run();
};


#endif //IME_WINDOW_H
