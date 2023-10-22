#pragma once

#include "scene.h"
#include "components/Camera.h"
#include "iShaderMediator.h"
#include <glm/mat4x4.hpp>

class CameraSystem
{
private:
	iShaderMediator* m_pShaderMediator;
public:
	// ctors & dtors
	CameraSystem(iShaderMediator* pShaderMediator);
	~CameraSystem();

	// Called each frame
	void UpdateUL(engine::Scene* pScene, std::string& shaderProgram);
};