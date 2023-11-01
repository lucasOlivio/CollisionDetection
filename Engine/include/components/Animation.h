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

	// Scale animation
	EntityID m_changeTo;
	float m_duration;
	int m_scaleRate; // Quantity per second that will increase

	void m_UpdateScale(double deltaTime);

public:
	AnimationComponent();
	virtual ~AnimationComponent();

	std::vector<std::string> models;
	std::string friendlyName;
	bool isWireframe;
	bool doNotLight;

	// Toggle animation on/off
	void Toggle();

	virtual void GetInfo(sComponentInfo& compInfoOut);
	virtual void SetParameter(sParameterInfo& parameterIn);

	void Update(double deltaTime, uint shaderID, iShaderInfo* pShaderInfo);

	void Render();
};