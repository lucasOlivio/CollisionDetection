#pragma once

#include "Component.h"
#include "common/drawInfo.h"
#include "EngineRenderer/iShaderInfo.h"
#include <vector>

class AnimationComponent : public Component
{
private:
	bool m_isActive;
	double m_elapsedTime;

	// Rotation animation
	float m_duration;
	glm::vec3 m_velocity; // Quantity per second that will increase

	void m_UpdateRotation(double deltaTime);

public:
	AnimationComponent();
	virtual ~AnimationComponent();

	std::vector<std::string> models;
	std::string friendlyName;
	bool isWireframe;
	bool doNotLight;

	// Will only set active to true/false
	void SetActive(bool isActive);

	// Toggle animation on/off, will also reset time
	void Toggle();

	virtual void GetInfo(sComponentInfo& compInfoOut);
	virtual void SetParameter(sParameterInfo& parameterIn);

	void Update(double deltaTime, uint shaderID, iShaderInfo* pShaderInfo);

	void Render();
};