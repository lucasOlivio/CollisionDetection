#include "components/Player.h"
#include "common/opengl.h"
#include "scene/iGameplayDirector.h"

glm::vec3 PlayerComponent::GetVelocity()
{
	return this->m_velocity;
}

void PlayerComponent::GetInfo(sComponentInfo& compInfoOut)
{
	compInfoOut.componentName = "player";
	compInfoOut.componentParameters.clear();

	this->AddCompParInfo("velocity", "vec3", this->m_velocity, compInfoOut);
}

void PlayerComponent::SetParameter(sParameterInfo& parameterIn)
{
	if (parameterIn.parameterName == "velocity") {
		this->m_velocity = parameterIn.parameterVec3Value;
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

	printf("Rotate Z+:  W\n");
	printf("Rotate Z-:  S\n");
	printf("Rotate X+:  D\n");
	printf("Rotate X-:  A\n");

	// Rotate
	//---------------------------------------------
	glm::vec3 rotateVelocity;
	if (keyInfo.pressedKey == GLFW_KEY_W && (keyInfo.action == GLFW_PRESS || keyInfo.action == GLFW_REPEAT))
	{
		rotateVelocity = this->m_velocity * glm::vec3(0, 0, 1);
	}
	else if (keyInfo.pressedKey == GLFW_KEY_S && (keyInfo.action == GLFW_PRESS || keyInfo.action == GLFW_REPEAT))
	{
		rotateVelocity = this->m_velocity * glm::vec3(0, 0, -1);
	}
	else if (keyInfo.pressedKey == GLFW_KEY_D && (keyInfo.action == GLFW_PRESS || keyInfo.action == GLFW_REPEAT))
	{
		rotateVelocity = this->m_velocity * glm::vec3(1, 0, 0);
	}
	else if (keyInfo.pressedKey == GLFW_KEY_A && (keyInfo.action == GLFW_PRESS || keyInfo.action == GLFW_REPEAT))
	{
		rotateVelocity = this->m_velocity * glm::vec3(-1, 0, 0);
	}
	else
	{
		return;
	}

	sParameterInfo param;
	param.parameterVec3Value = rotateVelocity;
	this->m_pGameplayDirector->SendAction("rotate", this->m_entityID, param);
}
