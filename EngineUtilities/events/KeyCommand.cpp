#include "events/KeyCommand.h"

KeyEvent* KeyCommand::m_pKeyEvent = nullptr;

void KeyCommand::SetKeyEvent(KeyEvent* pKeyEvent)
{
	KeyCommand::m_pKeyEvent = pKeyEvent;
}

void KeyCommand::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!m_pKeyEvent)
	{
		// Event not configured
		return;
	}
	m_pKeyEvent->UpdateKeyCallback(key, scancode, action, mods);
}
