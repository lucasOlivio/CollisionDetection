#pragma once

#include "Common/OpenGL.h"
#include "Manager/LightManager.h"
#include "Manager/MeshManager.h"
#include <string>

class SceneSystem {
public:
	LightManager* pLightManager;
	MeshManager* pMeshManager;

	SceneSystem();
	~SceneSystem();

	// Load all needed components for the scene
	bool Initialize(std::string sceneName, GLuint pShaderProgramID,
		VAOManager* pVAOManager);
	void Destroy(VAOManager* pVAOManager);
};