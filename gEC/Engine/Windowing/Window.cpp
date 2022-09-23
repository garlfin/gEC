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
#include "Asset/Texture/TextureCube.h"

namespace { const char* const ExtErr = " not supported."; }

#define DEBUG(x) std::cout << "DEBUG: " << x << std::endl
#define CAMERA_SPEED 0.1f
#define CAMERA_SENSITIVITY 0.1f
#define CHECK_EXTENSION(ext) if(!glfwExtensionSupported(ext)) throw std::runtime_error(std::string(ext).append(ExtErr));

static void DebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

Window::Window(glm::i16vec2 size, const char* title) : Size(size), Title(title), MState(WindowState::Render)
{
    if(!glfwInit()) throw std::runtime_error("Failed to create GLFW context.");

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    MWindow = glfwCreateWindow(Size.x, Size.y, title, nullptr, nullptr);

    if(MWindow == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW MWindow.");
    }
    glfwSetInputMode(MWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(MWindow);

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
    glEnable(GL_DEPTH_TEST);
    glDebugMessageCallback(DebugLog, nullptr);

    CHECK_EXTENSION("GL_ARB_bindless_texture");
}

void Window::Run()
{
    glViewport(0, 0, Size.x, Size.y);

    glClearColor(0, 0, 0, 1);

    ComponentManager<MeshRenderer> meshRendererManager(this);
    ComponentManager<Transform> transformManager(this);

    CamManager = new CameraManager(this);
    CamManager->CamBuffer()->Bind(0, BufferBindLocation::UniformBuffer);

    AssetManager<Texture> texManager;
    Texture2D* tex = texManager.Create<Texture2D>(this, "../gEC/shelly.pvr");
    TextureCube* skybox = texManager.Create<TextureCube>(this, "../gEC/sky.pvr");

    ShaderManager shaderManager;
    shaderManager.AddInclude("../include.glsl");
    Shader* diffuse = shaderManager.Create<Shader>(this, "../gEC/skybox.vert", "../gEC/skybox.frag", &shaderManager);

    Entity* test = new Entity(this);
    test->AddComponent(meshRendererManager.Create<MeshRenderer>(test));
    test->AddComponent(transformManager.Create<Transform>(test));

    Entity* camera = new Entity(this);
    camera->AddComponent(transformManager.Create<Transform>(camera));
    camera->GetComponent<Transform>()->Location = glm::vec3(0, 0, 0);
    camera->AddComponent(CamManager->Create<Camera>(camera, 0.1, 300, 40));
    camera->GetComponent<Camera>()->Set();

    diffuse->Use();

    GLBuffer<ObjectData> objDat(this, 1);
    objDat.Bind(1, BufferBindLocation::UniformBuffer);

    diffuse->SetUniform(1, skybox->handle());

    auto* camTransform = camera->GetComponent<Transform>();
    auto* triTransform = test->GetComponent<Transform>();

    double delta;
    double totalTime = 0;

    glm::vec2 prevCursorPos {};
    glm::vec2 cursorDelta;

    bool firstMouse = true;

    while (!glfwWindowShouldClose(MWindow))
    {
        delta = glfwGetTime() - totalTime;
        totalTime += delta;

        glfwSetWindowTitle(MWindow, std::to_string((int) round(1 / delta)).c_str());

        glm::dvec2 newPos;
        glfwGetCursorPos(MWindow, &newPos.x, &newPos.y);
        cursorDelta = (glm::vec2) newPos - prevCursorPos;
        if (firstMouse) { firstMouse = false; cursorDelta = glm::dvec2(0.0); }

        prevCursorPos = newPos;

        camTransform->Rotation.x = std::clamp(camTransform->Rotation.x + cursorDelta.y * CAMERA_SENSITIVITY, -89.0f, 89.0f);
        camTransform->Rotation.y += cursorDelta.x * CAMERA_SENSITIVITY;

        camTransform->Location.z = -5 - sin(totalTime * 3);

        MState = WindowState::Skybox;

        transformManager.OnUpdate(delta);
        CamManager->OnRender(delta);

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glDepthFunc(GL_LEQUAL);

        CamManager->InitFrame();
        objDat.ReplaceData((float*) &triTransform->Model, 64);

        meshRendererManager.OnRender(0);

        glfwSwapBuffers(MWindow);

        if(glfwGetKey(MWindow, GLFW_KEY_ESCAPE)) break;

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

const float Window::Aspect() {
    return (float) Size.x / Size.y;
}

static void DebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
    if(severity == GL_DEBUG_SEVERITY_HIGH) throw std::runtime_error(message);
    std::cout << message << std::endl;
}

