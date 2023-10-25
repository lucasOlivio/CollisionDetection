#include "events/KeyEvent.h"

KeyEvent::KeyEvent()
{
	this->m_pressedKey = 0;
	this->m_scanCode = 0;
	this->m_action = 0;
	this->m_mods = 0;
}

KeyEvent::~KeyEvent()
{
}

void KeyEvent::UpdateKey(int key, int scancode, int action, int mods)
{
	this->m_pressedKey = key;
	this->m_scanCode = scancode;
	this->m_action = action;
	this->m_mods = mods;
	this->Event::Notify(this);
}

int KeyEvent::GetKeyCallback()
{
	return this->m_pressedKey;
}

int KeyEvent::GetScanCode()
{
	return this->m_scanCode;
}

int KeyEvent::GetAction()
{
	return this->m_action;
}

int KeyEvent::GetMods()
{
	return this->m_mods;
}