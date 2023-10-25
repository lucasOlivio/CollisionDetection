#include "EngineRenderer/LightSystem.h"
#include "components/Light.h"

LightSystem::LightSystem(iShaderInfo* pShaderInfo, SceneView* pSceneView)
{
	this->m_pShaderInfo = pShaderInfo;
	this->m_pSceneView = pSceneView;
}

LightSystem::~LightSystem()
{
}

bool LightSystem::Initialize(int shaderID)
{
    // Go over each lights setting the ULs and initializing them
    for (this->m_pSceneView->First("light"); !this->m_pSceneView->IsDone(); this->m_pSceneView->Next())
    {
        EntityID id = this->m_pSceneView->CurrentKey();
        std::string ulBasePath = "theLights[" + std::to_string(id) + "].";

        LightComponent* pLight = this->m_pSceneView->CurrentValue<LightComponent>();
        pLight->SetupLight(shaderID, ulBasePath);
    }

    return true;
}
