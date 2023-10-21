#pragma once
#include "common/scene.h"
#include "common/components.h"
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
	bool Initialize(std::string basePath, myecs::sScene* pScene);
	void Destroy();

	// Called for each entity each frame
	void Update(uint entity, myecs::sScene* pScene, std::string& shaderProgramName);
	void Render(uint entity, myecs::sScene* pScene, std::string& shaderProgramName);
};