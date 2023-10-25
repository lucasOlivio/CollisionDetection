#pragma once

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
	KeyEvent();
	virtual ~KeyEvent();

	void UpdateKey(int key, int scancode, int action, int mods);

	int GetKeyCallback();
	int GetScanCode();
	int GetAction();
	int GetMods();
};