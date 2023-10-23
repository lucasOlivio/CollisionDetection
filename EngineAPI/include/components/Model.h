#pragma once

#include "Component.h"
#include <string>

class ModelComponent : public Component
{
public:
	std::string name;
	std::string friendlyName;
	bool isWireframe;
	bool doNotLight;

	virtual void GetInfo(sComponentInfo& compInfoOut);
	virtual void SetParameter(sParameterInfo& parameterIn);
};