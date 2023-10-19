#include "System/SceneSystem.h"
#include <iostream>


SceneSystem::SceneSystem()
{
    this->pLightManager = nullptr;
    this->pMeshManager = nullptr;
}

SceneSystem::~SceneSystem()
{
}

bool SceneSystem::Initialize(std::string sceneName, GLuint pShaderProgramID,
                            VAOManager* pVAOManager)
{
    this->pMeshManager = new MeshManager();
    if (!this->pMeshManager->Initialize(sceneName, pShaderProgramID, pVAOManager))
    {
        std::cout << "Error loading meshes!" << std::endl;
        return false;
    }

    this->pLightManager = new LightManager();
    if (!this->pLightManager->Initialize(sceneName, pShaderProgramID))
    {
        std::cout << "Error loading lights!" << std::endl;
        return false;
    }

    return true;
}

void SceneSystem::Destroy(VAOManager* pVAOManager)
{
    this->pLightManager->Destroy();
    this->pMeshManager->Destroy(pVAOManager);
    delete this->pLightManager;
    delete this->pMeshManager;
}