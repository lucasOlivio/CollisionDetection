#include "System/RenderingSystem.h"
#include "Common/Utils.h"
#include "Component/ModelInfo.h"
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// Load file configurations
const std::string KEYWORD_CAMERA_EYE = "cameraEye:";
const std::string KEYWORD_CAMERA_TARGET = "cameraTarget:";
const std::string KEYWORD_CAMERA_UP_VECTOR = "cameraUpVector:";

// Window config
const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

// Editor camera movement
const float CAMERA_MOVEMENT_SPEED = 0.1f;

RenderingSystem::RenderingSystem() {
    this->cameraEye = {};
    this->cameraTarget = {};
    this->upVector = {};

    this->pWindow = nullptr;
}

bool RenderingSystem::LoadSceneCamera(std::string sceneName)
{
    std::string fileName = this->m_GetCameraFileName(sceneName);
    std::ifstream cameraFile(fileName);
    std::string currString = "";

    while (cameraFile >> currString) {
        if (currString == KEYWORD_CAMERA_EYE) {
            glm::vec4 cameraEye;
            cameraFile >> cameraEye.x;
            cameraFile >> cameraEye.y;
            cameraFile >> cameraEye.z;
            this->cameraEye = cameraEye;
            continue;
        }
        if (currString == KEYWORD_CAMERA_TARGET) {
            glm::vec4 cameraTarget;
            cameraFile >> cameraTarget.x;
            cameraFile >> cameraTarget.y;
            cameraFile >> cameraTarget.z;
            this->cameraTarget = cameraTarget;
            continue;
        }
        if (currString == KEYWORD_CAMERA_UP_VECTOR) {
            glm::vec4 upVector;
            cameraFile >> upVector.x;
            cameraFile >> upVector.y;
            cameraFile >> upVector.z;
            this->upVector = upVector;
            continue;
        }
    }

    return true;
}

bool RenderingSystem::Initialize(std::string sceneName, GLFWerrorfun ErrorCallback, GLFWkeyfun KeyCallback) {
    // Setup camera
    // ------------------------------------------------
    this->LoadSceneCamera(sceneName);
    // ------------------------------------------------

    // Setup GLFW
    // ------------------------------------------------
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    this->pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, sceneName.c_str(), NULL, NULL);
    if (!this->pWindow) {
        return false;
    }

    glfwSetKeyCallback(this->pWindow, KeyCallback);

    glfwMakeContextCurrent(this->pWindow);
    glfwSwapInterval(1);
    // ------------------------------------------------

    // Setup GLAD
    // ------------------------------------------------
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // ------------------------------------------------

    return true;
}

// Destroy all glfw, glad and pointers objects
RenderingSystem::~RenderingSystem() {
    if (this->pWindow) {
        glfwDestroyWindow(this->pWindow);
    }
    glfwTerminate();
}

// Builds the standard file path for the camera
std::string RenderingSystem::m_GetCameraFileName(std::string sceneName)
{
    return "assets/database/" + sceneName + "-camera" + ".txt";
}

void RenderingSystem::m_UpdateViewport()
{
    int width, height;

    glfwGetFramebufferSize(this->pWindow, &width, &height);

    glViewport(0, 0, width, height);
}

void RenderingSystem::m_UpdateMatricesUniforms(GLint shaderProgramID, Mesh* pCurrentMesh)
{
    glm::mat4 matModel = glm::mat4(1.0f);   // Identity matrix
    pCurrentMesh->ApplyTransformations(matModel);

    GLint matModel_UL = glGetUniformLocation(shaderProgramID, "matModel");
    glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(matModel));

    glm::mat4 matProjection = this->GetProjection();
    GLint matProjection_UL = glGetUniformLocation(shaderProgramID, "matProjection");
    glUniformMatrix4fv(matProjection_UL, 1, GL_FALSE, glm::value_ptr(matProjection));


    glm::mat4 matView = this->GetView();
    GLint matView_UL = glGetUniformLocation(shaderProgramID, "matView");
    glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(matView));

    // Also calculate and pass the "inverse transpose" for the model matrix
    glm::mat4 matModel_InverseTranspose = glm::inverse(glm::transpose(matModel));
    GLint matModel_IT_UL = glGetUniformLocation(shaderProgramID, "matModel_IT");
    glUniformMatrix4fv(matModel_IT_UL, 1, GL_FALSE, glm::value_ptr(matModel_InverseTranspose));
}

// Draw all meshes using OpenGL and VAO
void RenderingSystem::DrawMesh(Mesh* pCurrentMesh, GLuint shaderProgramID, VAOManager* pVAOManager) {
    ModelDrawInfo* pModelInfo = pVAOManager->FindDrawInfoByModelName(pCurrentMesh->meshName);
    if (!pModelInfo) {
        return;
    }

    if (pCurrentMesh->isWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Set if the mesh should calculate lightning in shader
    GLint isIluminated_UL = glGetUniformLocation(shaderProgramID, "doNotLight");
    glUniform1f(isIluminated_UL, pCurrentMesh->doNotLight);

    glBindVertexArray(pModelInfo->VAOID); 		//  enable VAO (and everything else)
    glDrawElements(GL_TRIANGLES,
        pModelInfo->numberOfIndices,
        GL_UNSIGNED_INT,
        0);
    glBindVertexArray(0); 			            // disable VAO (and everything else)
}

glm::mat4 RenderingSystem::GetView()
{
    return glm::lookAt(this->cameraEye,
        this->cameraTarget,
        this->upVector);
}

glm::mat4 RenderingSystem::GetProjection()
{
    return glm::perspective(0.6f,
        this->GetCurrentWindowRatio(),
        0.1f,
        1000.0f);
}

void RenderingSystem::DrawAllMeshes(std::vector<Mesh*> meshesToDraw, GLuint shaderProgramID, VAOManager* pVAOManager) {
    for (unsigned int index = 0; index != meshesToDraw.size(); index++) {
        Mesh* pCurrentMesh = meshesToDraw[index];

        this->m_UpdateViewport();

        this->m_UpdateMatricesUniforms(shaderProgramID, pCurrentMesh);

        this->DrawMesh(pCurrentMesh, shaderProgramID, pVAOManager);
    }
}

float RenderingSystem::GetCurrentWindowRatio() {
    float ratio;
    int width, height;

    glfwGetFramebufferSize(this->pWindow, &width, &height);
    ratio = width / (float)height;
    return ratio;
}

bool RenderingSystem::WindowShouldClose() {
    return glfwWindowShouldClose(this->pWindow);
}

// Set window name using glfw and cameras positions
void RenderingSystem::SetWindowName(std::string windowName) {
    windowName = windowName + " | Camera (x,y,z): "
        + std::to_string(this->cameraEye.x) + ", "
        + std::to_string(this->cameraEye.y) + ", "
        + std::to_string(this->cameraEye.z) + ")";

    glfwSetWindowTitle(this->pWindow, windowName.c_str());
}

bool RenderingSystem::SaveSceneCameraToFile(std::string sceneName)
{
    std::string cameraFileName = this->m_GetCameraFileName(sceneName);

    // "O" for "output" file stream
    std::ofstream cameraFile(cameraFileName.c_str(), std::ofstream::trunc);

    cameraFile << KEYWORD_CAMERA_EYE << " " << this->cameraEye.x << " "
        << this->cameraEye.y << " "
        << this->cameraEye.z << " " << std::endl;
    cameraFile << KEYWORD_CAMERA_TARGET << " " << this->cameraTarget.x << " "
        << this->cameraTarget.y << " "
        << this->cameraTarget.z << std::endl;
    cameraFile << KEYWORD_CAMERA_UP_VECTOR << " " << this->upVector.x << " "
        << this->upVector.y << " "
        << this->upVector.z << std::endl;

    std::cout << "Saved succesfully!";

    return true;
}

bool RenderingSystem::MoveCamera(unsigned int axis, int orientation)
{
    if (axis > 2)
    {
        std::cout << "Axis must be: 0 for x, 1 for y or 2 for z!";
        return false;
    }
    if (orientation != -1 && orientation != 1)
    {
        std::cout << "Orientation must be -1 or 1!";
        return false;
    }

    // Change resource new position based on speed and orientation
    this->cameraEye[axis] += (orientation * CAMERA_MOVEMENT_SPEED);

    return true;
}

bool RenderingSystem::MoveCameraTarget(unsigned int axis, int orientation)
{
    if (axis > 2)
    {
        std::cout << "Axis must be: 0 for x, 1 for y or 2 for z!";
        return false;
    }
    if (orientation != -1 && orientation != 1)
    {
        std::cout << "Orientation must be -1 or 1!";
        return false;
    }

    // Change resource new target based on speed and orientation
    this->cameraTarget[axis] += (orientation * CAMERA_MOVEMENT_SPEED);

    return true;
}
