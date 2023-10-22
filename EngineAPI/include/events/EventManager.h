#pragma once

#include "Event.h"
#include "Listener.h"
#include <map>
#include <vector>

// Event mediator & singleton
class EventManager {
private:
    std::map<Event*, std::vector<Listener*>> m_eventListeners;
    static EventManager* m_pInstance;
    EventManager() {};

public:
    // deleting copy constructor
    EventManager(const EventManager& obj) = delete;

    static EventManager* GetInstance();
    static void DestroyInstance();

    // Subscribe a listener to an event
    void Subscribe(Event* pEvent, Listener* pListener);

    // Unsubscribe a listener from an event
    void Unsubscribe(Event* pEvent, Listener* pListener);

    // Notify listeners of an event
    void Notify(Event* pEvent);
};