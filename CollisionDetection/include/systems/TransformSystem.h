#pragma once

#include "types.h"
#include "scene.h"
#include "iShaderMediator.h"
#include <glm/mat4x4.hpp>

class TransformSystem
{
private:
	iShaderMediator* m_pShaderMediator;

	void m_ApplyTransform(engine::TransformComponent transform, glm::mat4& matModelOut);
public:
	// ctors & dtors
	TransformSystem(iShaderMediator* pShaderMediator);
	~TransformSystem();

	// Called for each entity each frame
	void UpdateUL(EntityID entityID, engine::Scene* pScene, std::string& shaderProgram);
};