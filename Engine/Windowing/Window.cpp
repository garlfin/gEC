//
// Created by scion on 8/29/2022.
//

#include "Window.h"
#include "../Asset/Mesh/VAO.h"
#include "../Asset/Material/Shader.h"
#include "../Struct/CameraData.h"
#include <stdexcept>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


static void DebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

Window::Window(glm::i16vec2 size, std::string const& title) : Size(size), Title(title), TextManager()
{
    if(!glfwInit()) throw std::runtime_error("Failed to create GLFW window.");

    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(Size.x, Size.y, Title.c_str(), nullptr, nullptr);

    if(window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    glDebugMessageCallback(DebugLog, nullptr);

    std::cout << "OpenGL Version: " << (char*)glGetString(GL_VERSION) << std::endl;
    std::cout << "Vendor: " << (char*)glGetString(GL_VENDOR) << std::endl;

    TextManager.Free();
}

void Window::Run() {

    glViewport(0, 0, Size.x, Size.y);

    glClearColor(0.6, 0.7, 1, 1);

    VAO tri(*this);
    Shader diffuse(*this, "default.vert", "default.frag");

    GLBuffer<CameraData> camDat(*this, 1);
    // Free the camera data once I'm done.
    {
        CameraData d{glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0), glm::vec3(0, 1, 0)),
                     glm::perspective(42.0f, (float) Size.x / Size.y, 0.1f, 300.0f)};
        camDat.ReplaceData(&d);
    }
    camDat.Bind(0, BufferBindLocation::UniformBuffer);

    diffuse.Use();
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        tri.Draw(1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    tri.Free();
    diffuse.Free();
    camDat.Free();

    glfwTerminate();
}

static void DebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
    std::cout << "Error Received: " << std::endl;
}

