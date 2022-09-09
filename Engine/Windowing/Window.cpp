//
// Created by scion on 8/29/2022.
//

#include "Window.h"
#include "../Asset/Mesh/VAO.h"
#include "../Asset/Material/Shader.h"
#include "../Struct/CameraData.h"
#include "../Asset/Texture/Texture2D.h"
#include "../Asset/AssetManager.h"
#include "../Component/Entity.h"
#include "../Component/MeshRenderer.h"
#include "../Component/ComponentManager.h"
#include <stdexcept>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#define DEG_TO_RAD ((float) std::numbers::pi / 180)
#define RAD_TO_DEG (180 / std::numbers::pi)


static void DebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

Window::Window(glm::i16vec2 size, const char* title) : Size(size), Title(title)
{
    if(!glfwInit()) throw std::runtime_error("Failed to create GLFW window.");

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(Size.x, Size.y, title, nullptr, nullptr);

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

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugLog, nullptr);

    std::cout << "OpenGL Version: " << (char*)glGetString(GL_VERSION) << std::endl;
    std::cout << "Vendor: " << (char*)glGetString(GL_VENDOR) << std::endl;

}

void Window::Run() {

    glViewport(0, 0, Size.x, Size.y);

    glClearColor(0.6, 0.7, 1, 1);

    Shader diffuse(this, "../default.vert", "../default.frag");
    //Texture2D tex(this, "../shelly.pvr");

    AssetManager<Texture> texManager;
    ComponentManager<MeshRenderer> meshRendererManager;
    Texture2D* tex = texManager.Create<Texture2D>(this, "../shelly.pvr");

    Entity* test = new Entity(this);
    test->AddComponent(meshRendererManager.Create<MeshRenderer>(test));

    diffuse.Use();

    GLBuffer<CameraData> camDat(this, 1);
    {
        CameraData d{glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0), glm::vec3(0, 1, 0)),
                     glm::perspective(50.0f * DEG_TO_RAD, (float) Size.x / Size.y, 0.1f, 300.0f)};
        camDat.ReplaceData(&d);
    }
    camDat.Bind(0, BufferBindLocation::UniformBuffer);

    diffuse.SetUniform(1, tex->Use(0));

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        meshRendererManager.OnRender(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    diffuse.Free();
    camDat.Free();
    texManager.Free();

    Entity* entity = new Entity(this);
    MeshRenderer* ptr = new MeshRenderer(entity);
    entity->AddComponent(ptr);

    delete ptr;


    glfwTerminate();
}

static void DebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
    if(severity == GL_DEBUG_SEVERITY_NOTIFICATION || severity == GL_DEBUG_SEVERITY_LOW) return;
    std::cout << message << std::endl;
}

