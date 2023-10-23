#pragma once

#include "scene/iScene.h"
#include "scene/SceneView.h"
#include "EngineRenderer/Renderer.h"
#include "EngineEditor/Editor.h"
#include "events/KeyEvent.h"

class Engine
{
private:
	bool m_isRunning;
	bool m_isInitialized;

	Renderer* m_pRenderer;
	Editor* m_pEditor;

	KeyEvent* m_pKeyEvent;

	iScene* m_pScene;
	SceneView* m_pSceneView;
public:
	// ctors & dtors
	Engine();
	~Engine();

	// Initializes all the systems, if anything go wrong we should stop here
	bool Initialize(const std::string& sceneName);
	void Destroy();

	// Called each frame
	void Update();

	bool IsRunning();
};