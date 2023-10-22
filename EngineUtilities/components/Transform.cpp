#include "components/Transform.h"

void engine::TransformComponent::SetOrientation(glm::vec4 value)
{
    this->m_qOrientation = glm::quat(value);
}

void engine::TransformComponent::AdjustOrientation(glm::vec4 value)
{
	// To combine quaternion values, you multiply them together
	// Make a quaternion that represents that CHANGE in angle
	glm::quat qChange = glm::quat(value);

	// Multiply them together to get the change
	// Just like with matrix math
	this->m_qOrientation *= qChange;
}

glm::quat engine::TransformComponent::GetQuatOrientation()
{
    return this->m_qOrientation;
}
