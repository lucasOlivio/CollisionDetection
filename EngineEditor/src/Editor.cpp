#include "EngineEditor/Editor.h"
#include "components.h" // TODO: Find a way to remove this dependency
#include "components/iComponent.h"
#include "common/opengl.h"
#include "common/utils.h"

float changeStep = 0.1f;

Editor::Editor(KeyEvent* pKeyEvent, SceneView* pSceneView)
{
	pKeyEvent->Attach(this);

	this->m_pSceneView = pSceneView;
	this->m_selectedEntity = 0;
	this->m_isRunning = true;
}

Editor::~Editor()
{
}

void Editor::RedrawEntityUI()
{
	system("cls");

	this->m_vecCompInfos = this->m_pSceneView->GetComponentsInfo(this->m_selectedEntity);
	printf("Change step: %.2f\n", changeStep);
	for (sComponentInfo info : this->m_vecCompInfos)
	{
		printf("Component: %s\n", info.componentName.c_str());
		printf("%s\n", std::string(10, '-').c_str());
		for (sParameterInfo parameterInfo : info.componentParameters)
		{
			printf("%s: %s\n", parameterInfo.parameterName.c_str(), parameterInfo.parameterValue.c_str());
		}
		printf("%s\n", std::string(50, '=').c_str());
	}

	return;
}

void Editor::Notify(iEvent* pEvent)
{
	KeyEvent* pKeyEvent = dynamic_cast<KeyEvent*>(pEvent);
	
	this->KeyActions(pKeyEvent->GetKeyCallback(),
					 pKeyEvent->GetScanCode(), 
					 pKeyEvent->GetAction(), 
					 pKeyEvent->GetMods());

	this->RedrawEntityUI();
}

bool Editor::IsRunning()
{
	return this->m_isRunning;
}

void Editor::KeyActions(int key, int scancode, int action, int mods)
{
	// Close window
	if (key == GLFW_KEY_ESCAPE && (action == GLFW_PRESS))
	{
		this->m_isRunning = false;
		return;
	}

	// Entity selection
	// --------------------------------------------
	if (key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->ChangeSelectedEntity(1);
		return;
	}
	if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->ChangeSelectedEntity(-1);
		return;
	}

	// Change step
	// --------------------------------------------
	if (key == GLFW_KEY_KP_ADD && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		changeStep += 0.1;
		return;
	}
	if (key == GLFW_KEY_KP_SUBTRACT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		changeStep -= 0.1;
		return;
	}

	//// Transform position
	//// --------------------------------------------
	//if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	//{
	//	this->MoveTransform(0, changeStep);
	//	return;
	//}
	//if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	//{
	//	this->MoveTransform(0, -changeStep);
	//	return;
	//}

	//if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
	//{
	//	this->MoveTransform(1, changeStep);
	//	return;
	//}
	//if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
	//{
	//	this->MoveTransform(1, -changeStep);
	//	return;
	//}

	//if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	//{
	//	this->MoveTransform(2, changeStep);
	//	return;
	//}
	//if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	//{
	//	this->MoveTransform(2, -changeStep);
	//	return;
	//}
}

void Editor::ChangeSelectedEntity(int orientation)
{
	using namespace myutils;

	// Make sure we don't over step
	orientation = Sign(orientation);

	this->m_selectedEntity += orientation;
	int numEntities = this->m_pSceneView->GetNumEntities();
	WrapMinMax<int>(0, numEntities, this->m_selectedEntity);

	return;
}