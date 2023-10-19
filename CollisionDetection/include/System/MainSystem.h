#pragma once

#include "System/RenderingSystem.h"
#include "System/SceneSystem.h"
#include "Manager/ShaderManager.h"

class MainSystem
{
public:
	// Systems managed by the main system
	RenderingSystem* pRenderingSystem;
	SceneSystem* pSceneSystem;

	// Managers managed by the main system
	ShaderManager* pShaderManager;
	VAOManager* pVAOManager;

	// Scene been rendered
	std::string sceneName;

	// ctors dtors
	MainSystem();
	~MainSystem();

	// Setup whole scene and windows using the respective systems
	bool Initialize(std::string sceneName, GLFWerrorfun ErrorCallback, GLFWkeyfun KeyCallback);
	void Destroy();

	// Save all components configurations to database files
	void Save();

	// Destroy all systems and load all again from the db files
	void Reload();

	// Main loop for rendering and all events
	void MainLoop();
};