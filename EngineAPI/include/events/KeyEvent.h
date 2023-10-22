#pragma once

#include "opengl.h"
#include "Event.h"

// Key callback events triggered by glfw on window
class KeyEvent : public Event
{
private:
	int m_pressedKey;
	int m_scanCode;
	int m_action;
	int m_mods;
public:
	KeyEvent(EventManager* pEventManager);

	void UpdateKeyCallback(int key, int scancode, int action, int mods);
	void GetKeyCallback(int& key, int& scancode, int& action, int& mods);
};