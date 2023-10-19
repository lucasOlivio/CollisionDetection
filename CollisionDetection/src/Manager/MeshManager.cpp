#include "Manager/MeshManager.h"
#include "Common/Utils.h"
#include <fstream>
#include <iostream>

// Load file configurations
const std::string KEYWORD_NEW_MESH = "***"; // Represents the begining of a new mesh data bellow
const std::string KEYWORD_MESH_NAME = "name:";
const std::string KEYWORD_MESH_NICKNAME = "nickname:";
const std::string KEYWORD_MESH_POSITION = "position:";
const std::string KEYWORD_MESH_ORIENTATION = "orientation:";
const std::string KEYWORD_MESH_SCALE = "scale:";
const std::string KEYWORD_MESH_WIREFRAME = "isWireframe:";
const std::string KEYWORD_MESH_NOT_LIGHT = "doNotLight:";

// Edit mesh in scene
const float MESH_MOVEMENT_SPEED = 0.01f;
const float MESH_ROTATION_SPEED = 0.3f;
const float MESH_SCALING_SPEED = 0.05f;

// ctors dtors
MeshManager::MeshManager()
{
    this->m_pMeshes = {};
    this->m_indexSelectedMesh = 0;
}

MeshManager::~MeshManager()
{
}

// Loads all meshes that will be drawn into the scene
bool MeshManager::m_LoadMeshesFromFile(std::string fileName)
{
    // "i" for "input" file stream
    std::ifstream meshesFile(fileName.c_str());

    if (!meshesFile.is_open()) {
        std::cout << "Error opening file " << fileName << std::endl;
        return false;
    }

    // keyword new mesh is the first command in structure, so we need to start from -1 so the first index will be 0
    int currIndex = -1;
    std::string currString = "";
    while (meshesFile >> currString) {
        if (currString == KEYWORD_NEW_MESH) {
            this->m_pMeshes.push_back(new Mesh());
            currIndex += 1;
            continue;
        }
        if (currString == KEYWORD_MESH_NAME) {
            meshesFile >> this->m_pMeshes[currIndex]->meshName;
            if (this->m_pMeshes[currIndex]->meshNickname == "")
            {
                this->m_pMeshes[currIndex]->meshNickname = this->m_pMeshes[currIndex]->meshName;
            }
            continue;
        }
        if (currString == KEYWORD_MESH_NICKNAME) {
            meshesFile >> this->m_pMeshes[currIndex]->meshNickname;
            continue;
        }
        if (currString == KEYWORD_MESH_POSITION) {
            glm::vec3 position = {};
            meshesFile >> position.x;
            meshesFile >> position.y;
            meshesFile >> position.z;
            this->m_pMeshes[currIndex]->SetPosition(position);
            continue;
        }
        if (currString == KEYWORD_MESH_ORIENTATION) {
            glm::vec3 orientation = {};
            meshesFile >> orientation.x;
            meshesFile >> orientation.y;
            meshesFile >> orientation.z;
            this->m_pMeshes[currIndex]->SetOrientation(orientation);
            continue;
        }
        if (currString == KEYWORD_MESH_SCALE) {
            float scale = 0.0f;
            meshesFile >> scale;
            this->m_pMeshes[currIndex]->SetScale(scale);
            continue;
        }
        if (currString == KEYWORD_MESH_WIREFRAME) {
            bool isWireframe = false;
            meshesFile >> isWireframe;
            this->m_pMeshes[currIndex]->isWireframe = isWireframe;
            continue;
        }
        if (currString == KEYWORD_MESH_NOT_LIGHT) {
            bool doNotLight = false;
            meshesFile >> doNotLight;
            this->m_pMeshes[currIndex]->doNotLight = doNotLight;
            continue;
        }
    }

    return true;
}

// Builds the standard file path for the meshes
std::string MeshManager::m_GetMeshesFileName(std::string sceneName)
{
    return "assets/database/" + sceneName + "-models.txt";
}

bool MeshManager::Initialize(std::string sceneName, GLuint pShaderProgramID,
    VAOManager* pVAOManager)
{
    bool isMeshLoaded = this->LoadSceneMeshes(sceneName, pShaderProgramID, pVAOManager);
    if (!isMeshLoaded)
    {
        printf("Error loading meshes from file!\n");
        return false;
    }
    return true;
}

void MeshManager::Destroy(VAOManager* pVAOManager)
{
    for (Mesh* mesh : this->m_pMeshes)
    {
        pVAOManager->DestroyVBO(mesh->meshName);
        delete mesh;
    }
    this->m_pMeshes.clear();
}

std::vector<Mesh*> MeshManager::GetMeshes()
{
    return this->m_pMeshes;
}

Mesh* MeshManager::GetMesh(unsigned int index)
{
    if (index > this->m_pMeshes.size())
    {
        std::cout << "Mesh index bigger than array!" << std::endl;
        return nullptr;
    }
    return this->m_pMeshes[index];
}

Mesh* MeshManager::FindMeshByNickname(std::string nickName)
{
    for (unsigned int index = 0; index != this->m_pMeshes.size(); index++)
    {
        Mesh* pCurrentMesh = this->m_pMeshes[index];

        if (pCurrentMesh->meshNickname == nickName)
        {
            return pCurrentMesh;
        }
    }

    // Didn't find it
    return nullptr;
}

bool MeshManager::LoadSceneMeshes(std::string sceneName, GLuint pShaderProgramID,
                                    VAOManager* pVAOManager)
{
    std::string meshesFileName = this->m_GetMeshesFileName(sceneName);

    // Loads all meshes that will be drawn into the RenderingSystem vector
    if (!this->m_LoadMeshesFromFile(meshesFileName)) {
        std::cout << "Error loading scene meshes <" << meshesFileName << ">. Make sure there is a .txt file with its configurations..." << std::endl;
        return false;
    }

    // Load all models information (vertex, indices) into VAO
    for (Mesh* meshInfo : this->m_pMeshes) {
        pVAOManager->LoadModelIntoVAO(meshInfo->meshName, pShaderProgramID);
    }

    return true;
}

bool MeshManager::SaveSceneMeshesToFile(std::string sceneName)
{
    std::string meshesFileName = this->m_GetMeshesFileName(sceneName);

    // "O" for "output" file stream
    std::ofstream meshesFile(meshesFileName.c_str(), std::ofstream::trunc);

    for (unsigned int index = 0; index != this->m_pMeshes.size(); index++)
    {
        meshesFile << std::endl;
        meshesFile << KEYWORD_NEW_MESH << std::endl;
        meshesFile << KEYWORD_MESH_NAME << " " << this->m_pMeshes[index]->meshName << std::endl;
        meshesFile << KEYWORD_MESH_NICKNAME << " " << this->m_pMeshes[index]->meshNickname << std::endl;

        glm::vec3 position = this->m_pMeshes[index]->GetPosition();
        meshesFile << KEYWORD_MESH_POSITION << " " << position.x << " "
            << position.y << " "
            << position.z << std::endl;

        glm::vec3 orientation = this->m_pMeshes[index]->GetOrientation();
        meshesFile << KEYWORD_MESH_ORIENTATION << " " << orientation.x << " "
            << orientation.y << " "
            << orientation.z << std::endl;

        float scale = this->m_pMeshes[index]->GetScale();
        meshesFile << KEYWORD_MESH_SCALE << " " << scale << std::endl;

        bool isWireframe = this->m_pMeshes[index]->isWireframe;
        meshesFile << KEYWORD_MESH_WIREFRAME << " " << isWireframe << std::endl;

        bool doNotLight = this->m_pMeshes[index]->doNotLight;
        meshesFile << KEYWORD_MESH_NOT_LIGHT << " " << doNotLight << std::endl;
    }

    std::cout << "Saved succesfully!";

    return true;
}

// Editor controls
// ----------------------------------------------------------------------
bool MeshManager::MoveSelectedMesh(unsigned int axis, int orientation)
{
    if (axis > 2)
    {
        std::cout << "Axis must be: 0 for x, 1 for y or 2 for z!";
        return false;
    }
    orientation = mymath::Sign(orientation);

    // Change resource new position based on speed and orientation
    Mesh* pSelectedMesh = this->GetMesh(this->m_indexSelectedMesh);
    glm::vec3 position = pSelectedMesh->GetPosition();
    position[axis] += (orientation * MESH_MOVEMENT_SPEED);

    // Set new position to resource
    pSelectedMesh->SetPosition(position);

    return true;
}

bool MeshManager::RotateSelectedMesh(unsigned int axis, int orientation)
{
    if (axis > 2)
    {
        std::cout << "Axis must be: 0 for x, 1 for y or 2 for z!";
        return false;
    }
    orientation = mymath::Sign(orientation);

    // Change resource new rotation based on speed and orientation
    Mesh* pSelectedMesh = this->GetMesh(this->m_indexSelectedMesh);
    glm::vec3 rotation = pSelectedMesh->GetOrientation();
    rotation[axis] += (orientation * MESH_ROTATION_SPEED);

    // Set new rotation to resource
    pSelectedMesh->SetOrientation(rotation);

    return true;
}

bool MeshManager::ChangeScaleSelectedMesh(int orientation)
{
    orientation = mymath::Sign(orientation);

    // Change resource new scale based on scale speed % and orientation
    Mesh* pSelectedMesh = this->GetMesh(this->m_indexSelectedMesh);
    float scale = pSelectedMesh->GetScale();
    scale *= ((orientation * MESH_SCALING_SPEED) + 1.0f);

    // TODO: Set a min limit of 0.1 and max of 100
    // Set new scale to resource
    pSelectedMesh->SetScale(scale);

    return true;
}

void MeshManager::ChangeSelectedMesh(int orientation)
{
    orientation = mymath::Sign(orientation);

    this->m_indexSelectedMesh += orientation;

    if (this->m_indexSelectedMesh >= this->m_pMeshes.size())
    {
        this->m_indexSelectedMesh = 0;
    }
    else if (this->m_indexSelectedMesh < 0)
    {
        this->m_indexSelectedMesh = this->m_pMeshes.size() - 1;
    }

    Mesh* pSelectedMesh = this->GetMesh(this->m_indexSelectedMesh);
    std::cout << "Selected model: " << pSelectedMesh->meshNickname << std::endl;
}
// ----------------------------------------------------------------------