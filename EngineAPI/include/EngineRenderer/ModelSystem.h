#pragma once

#include "scene/SceneView.h"
#include "VAOManager.h"
#include "iShaderInfo.h"
#include <glm/mat4x4.hpp>

class ModelSystem
{
private:
	VAOManager* m_pVAOManager;
	iShaderInfo* m_pShaderInfo;
	SceneView* m_pSceneView;

	void m_ApplyTransformInModelMat(iComponent* pTransform, glm::mat4& matModelOut);
public:
	// ctors & dtors
	ModelSystem(iShaderInfo* pShaderInfo, SceneView* pSceneView);
	~ModelSystem();

	// Where we really start/destroy everything that could go wrong
	bool Initialize(std::string basePath, int shaderID);
	void Destroy();

	// Called for each entity each frame
	void UpdateUL(EntityID entityID, int shaderID);
	void Render(EntityID entityID);
};