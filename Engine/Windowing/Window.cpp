//
// Created by scion on 8/29/2022.
//

#include "Window.h"
#include "../Asset/Mesh/VAO.h"
#include "../Asset/Material/Shader.h"
#include "../Asset/Texture/Texture2D.h"
#include "../Asset/AssetManager.h"
#include "../Component/Entity.h"
#include "../Component/Components/MeshRenderer.h"
#include "../Asset/Material/ShaderManager.h"
#include <stdexcept>
#include <iostream>
#include "../Misc/Math.h"
#include "../Component/Components/Transform.h"
#include "../Struct/ObjectData.h"
#include "Component/Managers/CameraManager.h"

#define DEBUG(x) std::cout << "DEBUG: " << x << std::endl

static void DebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

Window::Window(glm::i16vec2 size, const char* title) : Size(size), Title(title)
{
    if(!glfwInit()) throw std::runtime_error("Failed to create GLFW context.");

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

    int32_t outVer;
    int32_t outMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &outVer);
    glGetIntegerv(GL_MINOR_VERSION, &outMinor);

    std::cout << "OpenGL Version: " << (char*)glGetString(GL_VERSION) << "\n";
    std::cout << "Vendor: " << (char*)glGetString(GL_VENDOR) << "\n";
    std::cout << "Version: " << outVer << "." << outMinor << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugLog, nullptr);

}

void Window::Run() {
    glViewport(0, 0, Size.x, Size.y);

    glClearColor(0.2, 0.5, 1, 1);

    ComponentManager<MeshRenderer> meshRendererManager;
    ComponentManager<Transform> transformManager;

    CamManager = new CameraManager(this);
    CamManager->CamBuffer()->Bind(0, BufferBindLocation::UniformBuffer);

    AssetManager<Texture> texManager;
    Texture2D* tex = texManager.Create<Texture2D>(this, "../shelly.pvr");

    ShaderManager shaderManager;
    shaderManager.AddInclude("../include.glsl");
    Shader* diffuse = shaderManager.Create<Shader>(this, "../default.vert", "../default.frag", &shaderManager);

    Entity* test = new Entity(this);
    test->AddComponent(meshRendererManager.Create<MeshRenderer>(test));
    test->AddComponent(transformManager.Create<Transform>(test));

    Entity* camera = new Entity(this);
    camera->AddComponent(transformManager.Create<Transform>(camera));
    camera->GetComponent<Transform>()->Rotation = glm::vec3(90, 90, 0);
    camera->AddComponent(CamManager->Create<Camera>(camera, 0.1, 300, 60));
    camera->GetComponent<Camera>()->Set();

    diffuse->Use();


    GLBuffer<ObjectData> objDat(this, 1);
    objDat.Bind(1, BufferBindLocation::UniformBuffer);

    //diffuse->SetUniform(1, tex->handle());

    auto* camTransform = camera->GetComponent<Transform>();
    auto* triTransform = test->GetComponent<Transform>();

    double delta;
    double totalTime = 0;

    while (!glfwWindowShouldClose(window))
    {
        delta = glfwGetTime() - totalTime;
        totalTime += delta;

        triTransform->Rotation.y += delta * 5;

        if (glfwGetKey(window, GLFW_KEY_W)) camTransform->Location.z += .1 * delta;
        if (glfwGetKey(window, GLFW_KEY_A)) camTransform->Location.x -= .1 * delta;
        if (glfwGetKey(window, GLFW_KEY_S)) camTransform->Location.z -= .1 * delta;
        if (glfwGetKey(window, GLFW_KEY_D)) camTransform->Location.x += .1 * delta;

        transformManager.OnUpdate(delta);
        CamManager->OnRender(delta);

        glClear(GL_COLOR_BUFFER_BIT);

        CamManager->InitFrame();
        objDat.ReplaceData(&triTransform->Model, sizeof(glm::mat4));

        meshRendererManager.OnRender(0);

        glfwSwapBuffers(window);

        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) break;

        glfwPollEvents();
    }

    meshRendererManager.Free();
    texManager.Free();
    shaderManager.Free();
    CamManager->Free();

    delete test;
    delete camera;
    delete CamManager;

    glfwTerminate();
}

float Window::Aspect() {
    return (float) Size.x / Size.y;
}

static void DebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
    //if(severity == GL_DEBUG_SEVERITY_HIGH) throw std::runtime_error(message);
    std::cout << message << std::endl;

}

