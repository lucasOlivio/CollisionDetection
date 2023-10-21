#pragma once
#include "iShaderMediator.h"
#include "common/types.h"
#include "common/opengl.h"
#include <glm/mat4x4.hpp>

class WindowSystem
{
private:
	GLFWwindow* m_pWindow;

	iShaderMediator* m_pShaderMediator;
public:
	// ctors & dtors
	WindowSystem(iShaderMediator* pShaderMediator);
	~WindowSystem();

	// Where we really start/destroy everything that could go wrong
	bool Initialize(uint width, uint height, const std::string& windowName);
	void Destroy();

	// Called each frame
	void Update(std::string& shaderProgramName);
};