#include "System/MainSystem.h"
#include "Common/OpenGL.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> 
#include <iostream>

MainSystem::MainSystem()
{
    this->pRenderingSystem = nullptr;
    this->pSceneSystem = nullptr;
    this->pShaderManager = nullptr;
    this->pVAOManager = nullptr;
}

MainSystem::~MainSystem()
{
}

bool MainSystem::Initialize(std::string sceneName, GLFWerrorfun ErrorCallback, GLFWkeyfun KeyCallback)
{
    this->sceneName = sceneName;

    // Window, GLFW, rendering setup
    // ------------------------------------------------
    this->pRenderingSystem = new RenderingSystem();
    if (!this->pRenderingSystem->Initialize(this->sceneName, ErrorCallback, KeyCallback))
    {
        std::cout << "Error setting up rendering system!" << std::endl;
        return false;
    }
    // ------------------------------------------------

    // VAOManager
    // ------------------------------------------------
    this->pVAOManager = new VAOManager();
    // ------------------------------------------------

    // Setup Shaders and program
    // ------------------------------------------------
    this->pShaderManager = new ShaderManager();
    this->pShaderManager->SetBasePath("assets/shaders/");

    ShaderManager::Shader vertexShader;
    vertexShader.fileName = "vertexShader01.glsl";

    ShaderManager::Shader fragmentShader;
    fragmentShader.fileName = "fragmentShader01.glsl";

    if (!this->pShaderManager->CreateProgramFromFile("shader01", vertexShader, fragmentShader)) {
        std::cout << "Error: Couldn't compile or link:" << std::endl;
        std::cout << this->pShaderManager->GetLastError();
        exit(EXIT_FAILURE);
    }
    GLint shaderProgramID = this->pShaderManager->GetIDFromShaderProgramName("shader01");
    glUseProgram(shaderProgramID);
    // ------------------------------------------------

    // Load all scene components
    // ------------------------------------------------
    this->pSceneSystem = new SceneSystem();
    this->pSceneSystem->Initialize(this->sceneName, shaderProgramID, this->pVAOManager);
    // ------------------------------------------------

    return true;
}

void MainSystem::Destroy()
{
    delete this->pRenderingSystem;
    delete this->pSceneSystem;
    delete this->pShaderManager;
    delete this->pVAOManager;
}

void MainSystem::Save()
{
    // Save the scene meshes to a file
    this->pSceneSystem->pMeshManager->SaveSceneMeshesToFile(this->sceneName);
    // Save lights to file
    this->pSceneSystem->pLightManager->SaveSceneLightsToFile(this->sceneName);
    // Save camera to file
    this->pRenderingSystem->SaveSceneCameraToFile(this->sceneName);

    printf("All saved!\n");
}

void MainSystem::Reload()
{
    // Destroy all components
    this->pSceneSystem->Destroy(this->pVAOManager);

    // Load again from files
    GLint shaderProgramID = this->pShaderManager->GetIDFromShaderProgramName("shader01");
    this->pSceneSystem->Initialize(this->sceneName, shaderProgramID, this->pVAOManager);
    this->pRenderingSystem->LoadSceneCamera(this->sceneName);

    printf("All reloaded!\n");
}

void MainSystem::MainLoop()
{
    double lastTime = glfwGetTime();
    while (!this->pRenderingSystem->WindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ---------------------------------------------
        // TODO: Its better to get the average delta time of the last 20 frames. And have a limit for the deltatime
        // Time per frame (more or less)
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        // ---------------------------------------------

        GLint shaderProgramID = this->pShaderManager->GetIDFromShaderProgramName("shader01");
        this->pShaderManager->UseShaderProgram(shaderProgramID);

        // While drawing a pixel, see if the pixel that's already there is closer or not?
        glEnable(GL_DEPTH_TEST);
        // (Usually) the default - does NOT draw "back facing" triangles
        glCullFace(GL_BACK);

        std::vector<Mesh*> sceneMeshes = this->pSceneSystem->pMeshManager->GetMeshes();
        this->pRenderingSystem->DrawAllMeshes(sceneMeshes, shaderProgramID, this->pVAOManager);

        // Update the title screen
        this->pRenderingSystem->SetWindowName(this->sceneName);

        glfwSwapBuffers(this->pRenderingSystem->pWindow);
        glfwPollEvents();
    }
}
