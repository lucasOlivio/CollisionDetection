#pragma once

#include "common/types.h"
#include "scene/SceneView.h"
#include "events/KeyEvent.h"
#include "events/iListener.h"

// For now only some info been printed on console
// and handling keycallbacks from glfw
class Editor : public iListener
{
private:
	int m_selectedEntity;
	SceneView* m_pSceneView;
	bool m_isRunning;
	std::vector<sComponentInfo> m_vecCompInfos;

public:
	// ctors & dtors
	Editor(KeyEvent* pKeyEvent, SceneView* pSceneView);
	~Editor();

	// TODO: The scene should be changed so that the systems can get only the
	// componen they need, to avoid the whole thing been passed everywhere 

	// Draw selected entity UI info
	void RedrawEntityUI();

	// On key callback we manage entities on the scene accordingly
	virtual void Notify(iEvent* pEvent);

	bool IsRunning();

	// TODO: Set changes to be handled by each component I think
	// without editor needing to know about all
	// 
	// Actions to take based on key pressed
	void KeyActions(int key, int scancode, int action, int mods);

	void ChangeSelectedEntity(int orientation);
};