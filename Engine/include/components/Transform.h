#pragma once

#include "Component.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

class TransformComponent : public Component
{
private:
	glm::quat m_qOrientation; // Rotation in quaternions
	glm::vec3 m_oldPosition;
	glm::vec3 m_position;
	float m_scale;

public:

	// Convert orientation from euler angles to quaternions
	void SetOrientation(glm::vec3 value);
	// Change orientation by the given amount
	void AdjustOrientation(glm::vec3 value);

	void Move(glm::vec3 deltaValue);
	void SetPosition(glm::vec3 value);
	// Recalculate old position by difference with the current
	void SetOldPosition();
	glm::vec3 GetPosition();
	glm::vec3 GetOldPosition();

	glm::quat GetQuatOrientation();
	// Convert orientation from quaternions to euler angles
	glm::vec3 GetOrientation();

	void SetScale(float value);
	float GetScale();

	virtual void GetInfo(sComponentInfo& compInfoOut);
	virtual void SetParameter(sParameterInfo& parameterIn);
};