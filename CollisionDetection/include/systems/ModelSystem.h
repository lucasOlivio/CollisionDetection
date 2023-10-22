#pragma once

#include "scene.h"
#include "components/Model.h"
#include "managers/VAOManager.h"
#include "iShaderMediator.h"

class ModelSystem
{
private:
	VAOManager* m_pVAOManager;
	iShaderMediator* m_pShaderMediator;
public:
	// ctors & dtors
	ModelSystem(iShaderMediator* pShaderMediator);
	~ModelSystem();

	// Where we really start/destroy everything that could go wrong
	bool Initialize(std::string basePath, std::string& shaderProgram, engine::Scene* pScene);
	void Destroy(engine::Scene* pScene);

	// Called for each entity each frame
	void UpdateUL(EntityID entityID, engine::Scene* pScene, std::string& shaderProgram);
	void Render(EntityID entityID, engine::Scene* pScene, std::string& shaderProgram);
};