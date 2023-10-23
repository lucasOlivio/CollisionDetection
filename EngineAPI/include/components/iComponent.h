#pragma once

#include <vector>
#include <string>

// Parsed info to be used decoupled
struct sParameterInfo
{
	std::string parameterName;
	std::string parameterType;
	std::string parameterValue;
};

struct sComponentInfo
{
	std::string componentName;
	std::vector<sParameterInfo> componentParameters;
};

class iComponent
{
public:
	virtual ~iComponent() {};

	virtual void GetInfo(sComponentInfo& compInfoOut) = 0;
	virtual void SetParameter(sParameterInfo& parameterIn) = 0;
};
