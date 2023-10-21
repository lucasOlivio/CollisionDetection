#pragma once
#include "common/scene.h"
#include "common/components.h"
#include "iShaderMediator.h"
#include <glm/mat4x4.hpp>

class CameraSystem
{
private:
	bool m_isInitialized;
	iShaderMediator* m_pShaderMediator;
public:
	// ctors & dtors
	CameraSystem(iShaderMediator* pShaderMediator);
	~CameraSystem();

	// Where we really start/destroy everything that could go wrong
	bool Initialize();
	void Destroy();

	// Called each frame
	void Update(uint entity, myecs::sScene* pScene, std::string& shaderProgramName);
};