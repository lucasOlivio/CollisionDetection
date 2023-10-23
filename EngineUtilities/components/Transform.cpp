#include "components/Transform.h"
#include "common/utils.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

void TransformComponent::SetOrientation(glm::vec3 value)
{
    this->m_qOrientation = glm::quat(value);
}

void TransformComponent::AdjustOrientation(glm::vec3 value)
{
	// To combine quaternion values, you multiply them together
	// Make a quaternion that represents that CHANGE in angle
	glm::quat qChange = glm::quat(value);

	// Multiply them together to get the change
	// Just like with matrix math
	this->m_qOrientation *= qChange;
}

void TransformComponent::Move(int axis, float value)
{
	// Validate axis in (0 x, 1 y, 2 z)
	if (axis > 2)
	{
		return;
	}

	this->position[axis] += value;
	return;
}

glm::quat TransformComponent::GetQuatOrientation()
{
    return this->m_qOrientation;
}

glm::vec3 TransformComponent::GetOrientation()
{
	return glm::eulerAngles(this->GetQuatOrientation());
}

void TransformComponent::GetInfo(sComponentInfo& compInfoOut)
{
	using namespace myutils;

	compInfoOut.componentName = "transform";
	compInfoOut.componentParameters.clear();

	this->AddCompParInfo("position", "vec4", glm::to_string(this->position), compInfoOut);
	this->AddCompParInfo("scale", "string", std::to_string(this->scale), compInfoOut);
	this->AddCompParInfo("orientation", "vec3", glm::to_string(this->GetOrientation()), compInfoOut);
}

void TransformComponent::SetParameter(sParameterInfo& parameterIn)
{
	using namespace myutils;

	if (parameterIn.parameterName == "position") {
		this->position = StringToVec4(parameterIn.parameterValue);
	}
	else if (parameterIn.parameterName == "orientation") {
		this->SetOrientation(StringToVec3(parameterIn.parameterValue));
	}
	else if (parameterIn.parameterName == "scale") {
		this->scale = std::stof(parameterIn.parameterValue);
	}

	return;
}