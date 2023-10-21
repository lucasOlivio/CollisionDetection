#pragma once
#include "common/scene.h"
#include "systems/ModelSystem.h"
#include "systems/TransformSystem.h"
#include "systems/WindowSystem.h"
#include "systems/CameraSystem.h"
#include "managers/ShaderManager.h"

class Engine
{
private:
	bool m_isInitialized;
	std::string m_shaderProgramName;

	ShaderManager* m_pShaderManager;

	ModelSystem* m_pModelSystem;
	TransformSystem* m_pTransformSystem;
	WindowSystem* m_pWindowSystem;
	CameraSystem* m_pCameraSystem;

	myecs::sScene* m_pScene;
public:
	// ctors & dtors
	Engine();
	~Engine();

	// Initializes all the systems, if anything go wrong we should stop here
	bool Initialize(const std::string& sceneName);
	void Destroy();

	// Called each frame
	void Update();
};