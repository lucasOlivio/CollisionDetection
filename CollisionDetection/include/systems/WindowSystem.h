#pragma once

#include "iShaderMediator.h"
#include "types.h"
#include "opengl.h"
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
	bool Initialize(uint width, uint height, const std::string& windowName, GLFWkeyfun KeyCallback);
	void Destroy();

	// Clear all and bind opengl parameters
	void NewFrame(std::string& shaderProgram);
	void UpdateUL(std::string& shaderProgram);
	// Swap frames and buffers
	void EndFrame();

	bool WindowShouldClose();

	float GetCurrentWindowRatio();
};