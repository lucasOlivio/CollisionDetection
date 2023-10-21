#pragma once
#include <string>

class iShaderMediator
{
public:
	virtual ~iShaderMediator() {};

	// Uses the current shader program to retrieve the given uniform location
	// (-1 if not found)
	virtual int GetUL(std::string& shaderProgramName, std::string& ulName) = 0;
};
