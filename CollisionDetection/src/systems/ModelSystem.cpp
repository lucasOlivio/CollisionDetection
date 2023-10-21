#include "systems/ModelSystem.h"

ModelSystem::ModelSystem(iShaderMediator* pShaderMediator)
{
    this->m_pShaderMediator = nullptr;
    this->m_pVAOManager = nullptr;
}

ModelSystem::~ModelSystem()
{
    delete this->m_pShaderMediator;
    delete this->m_pVAOManager;
}

bool ModelSystem::Initialize(std::string basePath, myecs::sScene* pScene)
{
    this->m_pVAOManager = new VAOManager();

    return true;
}

void ModelSystem::Destroy()
{
}

void ModelSystem::Update(uint entity, myecs::sScene* pScene, std::string& shaderProgramName)
{
}

void ModelSystem::Render(uint entity, myecs::sScene* pScene, std::string& shaderProgramName)
{
}
