#pragma once

class EventManager;
class Event;

class Listener
{
private:
	EventManager* m_pEventManager;
protected:
	Listener(EventManager* pEventManager);
public:
	virtual ~Listener();
	virtual void OnNotify(Event* pEvent) = 0;
};