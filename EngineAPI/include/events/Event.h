#pragma once

#include "Listener.h"
#include <string>

class EventManager;

// Event subject
class Event
{
private:
    EventManager* m_pEventManager;
protected:
    Event() {};

    // This method allows subjects to send events via the EventManager
    virtual void Notify(class Event* pEvent);
public:
    Event(EventManager* pManager);
    virtual ~Event();

    // These methods allow listeners to subscribe/unsubscribe to this subject
    virtual void Attach(Listener* pListener);
    virtual void Dettach(Listener* pListener);
};