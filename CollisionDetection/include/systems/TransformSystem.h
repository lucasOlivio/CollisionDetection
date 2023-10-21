#pragma once
#include "common/types.h"
#include "common/components.h"
#include "common/scene.h"
#include "iShaderMediator.h"
#include <glm/mat4x4.hpp>

class TransformSystem
{
private:
	iShaderMediator* m_pShaderMediator;

	void m_ApplyTransform(uint entity, glm::mat4& matModelOut);
public:
	// ctors & dtors
	TransformSystem(iShaderMediator* pShaderMediator);
	~TransformSystem();

	// Where we really start/destroy everything that could go wrong
	bool Initialize();
	void Destroy();

	// Called for each entity each frame
	void Update(uint entity, myecs::sScene* pScene, std::string& shaderProgramName);
};