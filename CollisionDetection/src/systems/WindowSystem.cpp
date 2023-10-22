#include "systems/WindowSystem.h"
#include "openglerrors.h"
#include "opengl.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

WindowSystem::WindowSystem(iShaderMediator* pShaderMediator)
{
    this->m_pWindow = nullptr;
    this->m_pShaderMediator = pShaderMediator;
}

WindowSystem::~WindowSystem()
{
}

bool WindowSystem::Initialize(uint windowWidth, uint windowHeight, const std::string& windowName, GLFWkeyfun KeyCallback)
{
    glfwSetErrorCallback(GlfwErrorCallback);
    if (!glfwInit()) {
        printf("Error initializing GLFW!\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    this->m_pWindow = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
    if (!this->m_pWindow)
    {
        printf("Error creating window '%s'!\n", windowName.c_str());
        glfwTerminate();
        return false;
    }
    glfwSetKeyCallback(this->m_pWindow, KeyCallback);

    glfwMakeContextCurrent(this->m_pWindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // Enabling error outputs
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    return true;
}

void WindowSystem::Destroy()
{
    if (this->m_pWindow) {
        glfwDestroyWindow(this->m_pWindow);
    }
    glfwTerminate();
}

void WindowSystem::NewFrame(std::string& shaderProgram)
{
    // Bind shaderprogram 
    this->m_pShaderMediator->UseShaderProgram(shaderProgram);

    // Update viewport
    int width, height;
    glfwGetFramebufferSize(this->m_pWindow, &width, &height);
    glViewport(0, 0, width, height);

    // Clear frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // While drawing a pixel, see if the pixel that's already there is closer or not?
    glEnable(GL_DEPTH_TEST);
    // set to not draw "back facing" triangles
    glCullFace(GL_BACK);
}

void WindowSystem::UpdateUL(std::string& shaderProgram)
{
    // Update matrix projection in shader
    glm::mat4 matProjection = glm::perspective(0.6f,
                                               this->GetCurrentWindowRatio(),
                                               0.1f,
                                               1000.0f);
    GLint matProjectionUL = this->m_pShaderMediator->GetUL(shaderProgram, "matProjection");
    glUniformMatrix4fv(matProjectionUL, 1, GL_FALSE, glm::value_ptr(matProjection));
}

void WindowSystem::EndFrame()
{
    glfwSwapBuffers(this->m_pWindow);
    glfwPollEvents();
}

bool WindowSystem::WindowShouldClose() {
    return glfwWindowShouldClose(this->m_pWindow);
}

float WindowSystem::GetCurrentWindowRatio() {
    float ratio;
    int width, height;

    glfwGetFramebufferSize(this->m_pWindow, &width, &height);
    ratio = width / (float)height;
    return ratio;
}