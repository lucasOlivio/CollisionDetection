#pragma once

#include "Event.h"
#include "common/types.h"
#include "events/sCollisionEvent.h"
#include <glm/vec3.hpp>
#include <map>

// Collision events triggered by physics engine
class CollisionEvent : public Event
{
private:
	std::vector<sCollisionEvent*> m_pFrameCollisions;
public:
	CollisionEvent();
	virtual ~CollisionEvent();

	// All collisions that happened in the frame
	void TriggerCollisions(std::vector<sCollisionEvent*> vecFrameCollisionsIn);
	// Single collision trigger
	void TriggerCollision(sCollisionEvent* pCollisionIn);

	// Override notify to send only to those colliding
	void Notify();
	void Notify(sCollisionEvent* pCollision);

	void Clear();

	std::vector<sCollisionEvent*>& GetCollisions();
};