#include "events/CollisionEvent.h"
#include "events/iCollisionListener.h"

CollisionEvent::CollisionEvent()
{
	this->m_pFrameCollisions.clear();
}

CollisionEvent::~CollisionEvent()
{
}

void CollisionEvent::TriggerCollisions(std::vector<sCollisionEvent*> pFrameCollisions)
{
	this->m_pFrameCollisions = pFrameCollisions;

	this->Notify();
}

void CollisionEvent::TriggerCollision(sCollisionEvent* pCollisionIn)
{
	this->Notify(pCollisionIn);
}

void CollisionEvent::Notify()
{
	for (sCollisionEvent* pCollision : this->m_pFrameCollisions)
	{
		this->Notify(pCollision);
	}
}

void CollisionEvent::Notify(sCollisionEvent* pCollision)
{
	// Notify only listeners that collided with their collision
	for (iListener* listener : this->m_pListeners)
	{
		iCollisionListener* pCollListener = (iCollisionListener*)listener;
		EntityID entityID = pCollListener->GetEntityID();

		if (entityID == pCollision->entityA || entityID == pCollision->entityB)
		{
			pCollListener->Notify(pCollision);
		}
	}
}

void CollisionEvent::Clear()
{
	this->m_pListeners.clear();
}

std::vector<sCollisionEvent*>& CollisionEvent::GetCollisions()
{
	return this->m_pFrameCollisions;
}
