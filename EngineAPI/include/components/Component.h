#pragma once

#include "iComponent.h"

class Component : public iComponent
{
protected:
	Component() {};

	// Parse to component paramenter info and add to vector of parameters
	virtual void AddCompParInfo(const std::string& name,
		const std::string& type,
		const std::string& value,
		sComponentInfo& compInfoOut);

public:
	virtual ~Component() {};

	virtual void GetInfo(sComponentInfo& compInfoOut) = 0;
	virtual void SetParameter(sParameterInfo& parameterIn) = 0;
};
