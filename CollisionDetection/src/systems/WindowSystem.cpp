#include "systems/WindowSystem.h"

WindowSystem::WindowSystem(iShaderMediator* pShaderMediator)
{
    this->m_pWindow = nullptr;
    this->m_pShaderMediator = pShaderMediator;
}

WindowSystem::~WindowSystem()
{
    delete this->m_pWindow;
}

bool WindowSystem::Initialize(uint windowWidth, uint windowHeight, const std::string& windowName)
{
    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    this->m_pWindow = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
    if (!this->m_pWindow)
    {
        printf("Error creating window '%s'!\n", windowName.c_str());
        return false;
    }

    glfwMakeContextCurrent(this->m_pWindow);
    glfwSwapInterval(1);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    return true;
}

void WindowSystem::Destroy()
{
}

void WindowSystem::Update(std::string& shaderProgramName)
{
}
