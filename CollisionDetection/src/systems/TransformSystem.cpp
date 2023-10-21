#include "systems/TransformSystem.h"

void TransformSystem::m_ApplyTransform(uint entity, glm::mat4& matModelOut)
{
}

TransformSystem::TransformSystem(iShaderMediator* pShaderMediator)
{
}

TransformSystem::~TransformSystem()
{
}

bool TransformSystem::Initialize()
{
    return false;
}

void TransformSystem::Destroy()
{
}

void TransformSystem::Update(uint entity, myecs::sScene* pScene, std::string& shaderProgramName)
{
}
