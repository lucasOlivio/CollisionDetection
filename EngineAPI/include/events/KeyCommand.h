#pragma once

#include "KeyEvent.h"

// Commander to send callbacks to events
class KeyCommand
{
private:
	static KeyEvent* m_pKeyEvent;
public:
	static void SetKeyEvent(KeyEvent* pKeyEvent);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};