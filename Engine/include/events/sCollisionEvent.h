#pragma once

#include "Event.h"
#include "common/types.h"
#include "EnginePhysics/PhysicsProperties.hpp"

struct sCollisionEvent
{
	EntityID entityA;
	EntityID entityB;
	eBodyType bodyTypeA;
	eBodyType bodyTypeB;
	sTriangle* pMeshTriangleCollision;
	glm::vec3 contactPointA;
	glm::vec3 contactPointB;
	glm::vec3 positionA;
	glm::vec3 positionB;
	glm::vec3 velocityAtCollisionA;
	glm::vec3 velocityAtCollisionB;
};