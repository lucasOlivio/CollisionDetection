#pragma once

#include "types.h"
#include <string>

class iShaderMediator
{
public:
	virtual ~iShaderMediator() {};

	// Uses the current shader program to retrieve the given uniform location
	// (-1 if not found)
	virtual int GetUL(std::string& shaderProgram, const char* ulName) = 0;
	// Uses the current shader program to retrieve the given attribute location
	// (-1 if not found)
	virtual int GetAL(std::string& shaderProgram, const char* alName) = 0;
	// Bind opengl to this shader program
	virtual bool UseShaderProgram(uint ID) = 0;
	virtual bool UseShaderProgram(std::string& shaderProgram) = 0;
};
