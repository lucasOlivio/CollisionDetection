#include "events/Event.h"
#include "events/EventManager.h"

Event::Event(EventManager* pManager)
	: m_pEventManager(pManager)
{
}

Event::~Event()
{
}

void Event::Notify(Event* pEvent)
{
	this->m_pEventManager->Notify(this);
}

void Event::Attach(Listener* pListener)
{
	this->m_pEventManager->Subscribe(this, pListener);
}

void Event::Dettach(Listener* pListener)
{
	this->m_pEventManager->Unsubscribe(this, pListener);
}
