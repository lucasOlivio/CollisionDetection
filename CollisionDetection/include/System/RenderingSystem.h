#pragma once

#include "Common/OpenGL.h"
#include "Manager/VAOManager.h"
#include "Component/Mesh.h"
#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

// TODO: Dealing with concurrency if the game goes multi-thread
class RenderingSystem {
private:
    // Builds the standard file path for the camera
    std::string m_GetCameraFileName(std::string sceneName);

    // Updates per frame
    void m_UpdateViewport();
    void m_UpdateMatricesUniforms(GLint shaderProgramID, Mesh* pCurrentMesh);
public:
    // ctors dtors
    RenderingSystem();
    ~RenderingSystem();

    // Setup camera and glfw
    bool Initialize(std::string sceneName, GLFWerrorfun ErrorCallback, GLFWkeyfun KeyCallback);
    void Destroy();

    // Load all camera configuration from scene file
    bool LoadSceneCamera(std::string sceneName);

    // Scene camera
    glm::vec3 cameraEye;
    glm::vec3 cameraTarget;
    glm::vec3 upVector;

    // GLFW
    GLFWwindow* pWindow;

    // Get matrices for view and projection
    glm::mat4 GetView();
    glm::mat4 GetProjection();

    // Draw all meshes in "vecMeshesToDraw" using OpenGL and VAO
    void DrawMesh(Mesh* pCurrentMesh, GLuint shaderProgramID, VAOManager* pVAOManager);
    void DrawAllMeshes(std::vector<Mesh*> meshesToDraw, GLuint shaderProgramID, VAOManager* pVAOManager);

    // Get current window ratio based on window
    float GetCurrentWindowRatio();

    // Checks if the window should close using GLFW flags
    bool WindowShouldClose();

    // Set window name using glfw and cameras positions
    void SetWindowName(std::string windowName);

    // Save all camera configurations into a file
    bool SaveSceneCameraToFile(std::string sceneName);

    /**
     * Move camera in the respective axis.
     *
     * @param axis - Axis where the resource will move (0 - x, 1 - y, 2 - z).
     * @param orientation - Orientation to move (-1 backwards, 1 forward).
     * @return Resource was moved or not.
     */
    bool MoveCamera(unsigned int axis, int orientation);
    bool MoveCameraTarget(unsigned int axis, int orientation);
};