#include "events/KeyEvent.h"

KeyEvent::KeyEvent(EventManager* pEventManager)
{
	this->m_pressedKey = 0;
	this->m_scanCode = 0;
	this->m_action = 0;
	this->m_mods = 0;

	this->Event::Event(pEventManager);
}

void KeyEvent::UpdateKeyCallback(int key, int scancode, int action, int mods)
{
	this->m_pressedKey = key;
	this->m_scanCode = scancode;
	this->m_action = action;
	this->m_mods = mods;
	this->Event::Notify(this);
}

void KeyEvent::GetKeyCallback(int& key, int& scancode, int& action, int& mods)
{
	key = this->m_pressedKey;
	scancode = this->m_scanCode;
	action = this->m_action;
	mods = this->m_mods;
}
