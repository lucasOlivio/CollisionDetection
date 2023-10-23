#pragma once

#include "Component.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

class TransformComponent : public Component
{
private:
	glm::quat m_qOrientation; // Rotation in quaternions
public:
	glm::vec4 position;
	float scale;

	// Convert orientation from euler angles to quaternions
	void SetOrientation(glm::vec3 value);
	// Change orientation by the given amount
	void AdjustOrientation(glm::vec3 value);

	// Change position by the given amount in the given axis
	void Move(int axis, float value);

	glm::quat GetQuatOrientation();
	// Convert orientation from quaternions to euler angles
	glm::vec3 GetOrientation();

	virtual void GetInfo(sComponentInfo& compInfoOut);
	virtual void SetParameter(sParameterInfo& parameterIn);
};