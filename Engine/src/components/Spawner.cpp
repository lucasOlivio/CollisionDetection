#include "components/Spawner.h"
#include "common/utils.h"
#include <glm/gtx/string_cast.hpp>

SpawnerComponent::SpawnerComponent()
{
    this->m_elapsedTime = 0;
}

SpawnerComponent::~SpawnerComponent()
{
}

void SpawnerComponent::GetInfo(sComponentInfo& compInfoOut)
{
    using namespace myutils;

    compInfoOut.componentName = "spawner";
    compInfoOut.componentParameters.clear();

    this->AddCompParInfo("isActive", "bool", this->m_isActive, compInfoOut);
    this->AddCompParInfo("type", "int", this->m_eSpawnType, compInfoOut);
    this->AddCompParInfo("timer", "float", this->m_timer, compInfoOut);
    this->AddCompParInfo("quantity", "int", this->m_quantity, compInfoOut);
    this->AddCompParInfo("randomAxis", "vec3", this->m_randomAxis, compInfoOut);
    this->AddCompParInfo("randomAmplitude", "vec3", this->m_randomAmplitude, compInfoOut);
}

void SpawnerComponent::SetParameter(sParameterInfo& parameterIn)
{
    using namespace myutils;

    if (parameterIn.parameterName == "isActive") {
        this->m_isActive = parameterIn.parameterBoolValue;
    }
    else if (parameterIn.parameterName == "type") {
        this->m_eSpawnType = (eSpawnType)parameterIn.parameterIntValue;
    }
    else if (parameterIn.parameterName == "timer") {
        this->m_timer = parameterIn.parameterFloatValue;
    }
    else if (parameterIn.parameterName == "quantity") {
        this->m_quantity = parameterIn.parameterIntValue;
    }
    else if (parameterIn.parameterName == "randomAxis") {
        this->m_randomAxis = parameterIn.parameterVec3Value;
    }
    else if (parameterIn.parameterName == "randomAmplitude") {
        this->m_randomAmplitude = parameterIn.parameterVec3Value;
    }

    return;
}

void SpawnerComponent::SetActive(bool isActive)
{
    this->m_isActive = isActive;
}

bool SpawnerComponent::IsActive()
{
    if (this->m_isActive)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SpawnerComponent::Spawn()
{

    // Generate a random position based on the axis and amplitude and generate the needed quantity
    for (int i = 0; i < this->m_quantity; i++)
    {
        sParameterInfo deltaPosition;
        deltaPosition.parameterVec3Value.x = myutils::GetRandFloat(-this->m_randomAmplitude.x, this->m_randomAmplitude.x);
        deltaPosition.parameterVec3Value.y = myutils::GetRandFloat(-this->m_randomAmplitude.y, this->m_randomAmplitude.y);
        deltaPosition.parameterVec3Value.z = myutils::GetRandFloat(-this->m_randomAmplitude.z, this->m_randomAmplitude.z);
        this->m_pGameplayDirector->SendAction("spawnMe", this->GetEntityID(), deltaPosition);
    }
}

void SpawnerComponent::Update(double deltaTime)
{
    if (!this->m_isActive)
    {
        return;
    }

    if (this->m_eSpawnType == eSpawnType::TIMER && this->m_elapsedTime >= this->m_timer)
    {
        this->Spawn();
        this->m_elapsedTime = 0;
        return;
    }

    this->m_elapsedTime += deltaTime;
}