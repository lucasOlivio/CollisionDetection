#include "components/Animation.h"
#include "common/utilsMat.h"
#include "common/opengl.h"
#include "common/constants.h"

AnimationComponent::AnimationComponent()
{
    this->m_changeTo = 0;
    this->m_elapsedTime = 0;
    this->m_duration = 0;
    this->m_scaleRate = 0;
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::m_UpdateScale(double deltaTime)
{
    if (this->m_elapsedTime >= this->m_duration)
    {
        if (this->m_changeTo == 0)
        {
            sParameterInfo ignore;
            this->m_pGameplayDirector->SendAction("destroy", this->GetEntityID(), ignore);
        }
        else
        {
            sParameterInfo newModel;
            newModel.parameterIntValue = this->m_changeTo;
            this->m_pGameplayDirector->SendAction("changeInto", this->GetEntityID(), newModel);
        }
    }

    float deltaScale = (this->m_scaleRate * (float)deltaTime);

    sParameterInfo delta;
    delta.parameterFloatValue = deltaScale;
    this->m_pGameplayDirector->SendAction("scaleTransform", this->GetEntityID(), delta);
}

void AnimationComponent::GetInfo(sComponentInfo& compInfoOut)
{
    compInfoOut.componentName = "animation";
    compInfoOut.componentParameters.clear();

    this->AddCompParInfo("isActive", "bool", this->m_isActive, compInfoOut);
    this->AddCompParInfo("duration", "float", this->m_duration, compInfoOut);
    this->AddCompParInfo("changeTo", "int", (int)this->m_changeTo, compInfoOut);
    this->AddCompParInfo("scaleRate", "int", this->m_scaleRate, compInfoOut);
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
    else if (parameterIn.parameterName == "scaleRate") {
        this->m_scaleRate = parameterIn.parameterIntValue;
    }
    else if (parameterIn.parameterName == "changeTo") {
        this->m_changeTo = parameterIn.parameterIntValue;
    }

    return;
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

    this->m_UpdateScale(deltaTime);
}

void AnimationComponent::Render()
{
}
