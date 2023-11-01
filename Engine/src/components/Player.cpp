#include "components/Player.h"
#include "common/opengl.h"
#include "scene/iGameplayDirector.h"
#include "common/constants.h"

glm::vec3 PlayerComponent::GetVelocity()
{
	return this->m_velocity;
}

void PlayerComponent::GetInfo(sComponentInfo& compInfoOut)
{
	compInfoOut.componentName = "player";
	compInfoOut.componentParameters.clear();

	this->AddCompParInfo("velocity", "vec3", this->m_velocity, compInfoOut);
	this->AddCompParInfo("acceleration", "vec3", this->m_acceleration, compInfoOut);
}

void PlayerComponent::SetParameter(sParameterInfo& parameterIn)
{
	if (parameterIn.parameterName == "velocity") {
		this->m_velocity = parameterIn.parameterVec3Value;
	}
	else if (parameterIn.parameterName == "acceleration") {
		this->m_acceleration = parameterIn.parameterVec3Value;
	}
}

void PlayerComponent::Notify(iEvent* pEvent)
{
	KeyEvent* pKeyEvent = dynamic_cast<KeyEvent*>(pEvent);
	this->PlayerActions(pKeyEvent->GetKeyInfo());
}

void PlayerComponent::SetPlaying(bool isPlaying)
{
	this->m_isPlaying = isPlaying;
}

void PlayerComponent::PlayerActions(sKeyInfo keyInfo)
{
	if (!this->m_isPlaying)
	{
		return;
	}

	system("cls");
	printf("Editor / Play mode: P\n");
	printf("Enable/Disable shields: SPACE\n");

	// Enable shields
	//---------------------------------------------
	if (keyInfo.pressedKey == GLFW_KEY_SPACE && (keyInfo.action == GLFW_PRESS))
	{
		sParameterInfo param;
		// New X position for the new sphere
		param.parameterFloatValue = myutils::GetRandFloat(-10, 10);
		// Force applied in new sphere
		param.parameterVec3Value = this->m_velocity;
		param.parameterVec4Value =  glm::vec4(this->m_acceleration, 1);
		// Calculate the force based on the new X position (always going towards the center 0)
		param.parameterVec3Value.x = -(param.parameterFloatValue / 5);
		this->m_pGameplayDirector->SendAction("shoot", this->m_entityID, param);
	}
	else
	{
		return;
	}
}
