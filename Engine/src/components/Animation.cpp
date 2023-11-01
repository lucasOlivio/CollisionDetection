#include "components/Animation.h"
#include "common/utilsMat.h"
#include "common/opengl.h"
#include "common/constants.h"

AnimationComponent::AnimationComponent()
{
    this->m_elapsedTime = 0;
    this->m_duration = 0;
    this->m_velocity = glm::vec3(0);
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::m_UpdateRotation(double deltaTime)
{
    if (this->m_duration > 0 && this->m_elapsedTime >= this->m_duration)
    {
        this->m_isActive = false;
    }

    sParameterInfo delta;
    delta.parameterVec3Value = this->m_velocity;
    this->m_pGameplayDirector->SendAction("rotate", this->GetEntityID(), delta);
}

void AnimationComponent::GetInfo(sComponentInfo& compInfoOut)
{
    compInfoOut.componentName = "animation";
    compInfoOut.componentParameters.clear();

    this->AddCompParInfo("isActive", "bool", this->m_isActive, compInfoOut);
    this->AddCompParInfo("duration", "float", this->m_duration, compInfoOut);
    this->AddCompParInfo("velocity", "vec3", this->m_velocity, compInfoOut);
}

void AnimationComponent::SetParameter(sParameterInfo& parameterIn)
{
    using namespace myutils;

    if (parameterIn.parameterName == "isActive") {
        this->m_isActive = parameterIn.parameterBoolValue;
    }
    else if (parameterIn.parameterName == "duration") {
        this->m_duration = parameterIn.parameterFloatValue;
    }
    else if (parameterIn.parameterName == "velocity") {
        this->m_velocity = parameterIn.parameterVec3Value;
    }

    return;
}

void AnimationComponent::SetActive(bool isActive)
{
    this->m_isActive = isActive;
}

void AnimationComponent::Toggle()
{
    if (this->m_isActive)
    {
        // Can't change while animation is running
        return;
    }

    this->m_isActive = true;

    this->m_elapsedTime = 0;
}

void AnimationComponent::Update(double deltaTime, uint shaderID, iShaderInfo* pShaderInfo)
{
    if (!this->m_isActive)
    {
        return;
    }

    this->m_elapsedTime += deltaTime;

    this->m_UpdateRotation(deltaTime);
}

void AnimationComponent::Render()
{
}
