#include "events/EventManager.h"

EventManager* EventManager::m_pInstance = nullptr;

EventManager* EventManager::GetInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new EventManager();
    }
    return m_pInstance;
}

void EventManager::Subscribe(Event* pEvent, Listener* pListener)
{
    this->m_eventListeners[pEvent].push_back(pListener);
}

void EventManager::Unsubscribe(Event* pEvent, Listener* pListener)
{
    auto it = this->m_eventListeners.find(pEvent);
    if (it == this->m_eventListeners.end()) {
        // Event not found
        return;
    }
    // Remove listener from event list
    auto& listeners = it->second;
    listeners.erase(std::remove(listeners.begin(), listeners.end(), pListener), listeners.end());
    
    return;
}

#include "events/KeyEvent.h"
void EventManager::Notify(Event* pEvent)
{
    auto it = this->m_eventListeners.find(pEvent);
    if (it == this->m_eventListeners.end()) 
    {
        // Event not found
        return;
    }
    // Notify all listeners
    auto& listeners = it->second;
    for (Listener* listener : listeners) {
        listener->OnNotify(pEvent);
    }

    return;
}
