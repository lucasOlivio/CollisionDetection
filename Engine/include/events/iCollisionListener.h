#pragma once

#include "common/types.h"
#include "events/iListener.h"
#include "events/sCollisionEvent.h"

class iCollisionListener : public iListener
{
public:
	virtual ~iCollisionListener() {};

	virtual void Notify(sCollisionEvent* pCollision) = 0;

	virtual EntityID GetEntityID() = 0;
};
