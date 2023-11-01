#include "EnginePhysics/Physics.h"
#include "components/Force.h"
#include "components/Collision.h"
#include "components/Spawner.h"
#include "common/utilsMat.h"
#include <glm/gtx/string_cast.hpp>

Physics::Physics(SceneView* pSceneView, CollisionEvent* pCollisionEvent)
{
	this->m_isRunning = false;
	this->m_pSceneView = pSceneView;
	this->m_pCollisionEvent = pCollisionEvent;
}

Physics::~Physics()
{

}

void Physics::ApplyForce(EntityID entityID, double deltaTime)
{
	ForceComponent* pForce = this->m_pSceneView->GetComponent<ForceComponent>(entityID, "force");
	if (!pForce || !pForce->IsActive())
	{
		// Entity don't have force, so nothing we can do
		return;
	}

	TransformComponent* pTransform = this->m_pSceneView->GetComponent<TransformComponent>(entityID, "transform");
	if (!pTransform)
	{
		// Entity don't have a transform, so nothing we can do
		return;
	}


	// Check if object have mass
	if (pForce->GetInverseMass() <= 0.0f)
	{
		return;
	}

	// Move towards point
	glm::vec3 adjustTowards = glm::vec3(1);
	if (pForce->GetAdjustValue() != glm::vec3(0))
	{
		// Get direction of adjustment
		glm::vec3 direction = pForce->GetAdjustTowards() - pTransform->GetPosition();
		adjustTowards = glm::normalize(direction) * pForce->GetAdjustValue();
	}

	// Explicit forward Euler "integration step"
	//	NewVelocity = LastVel + (Accel * DeltaTime)
	//	NewPosition = LastPos + (Vel * DeltaTime)	

	// Calculate new velocity this frame based on 
	// delta time, acceleration and current velocity
	glm::vec3 velThisFrame = (pForce->GetAcceleration() * adjustTowards * (float)deltaTime) + pForce->GetVelocity();
	pForce->SetVelocity(velThisFrame);
	// New object position
	glm::vec3 deltaPosition = velThisFrame * (float)deltaTime;

	pTransform->Move(deltaPosition);

	return;
}

void Physics::ResolveCollision(sCollisionEvent* pCollisionEvent, TransformComponent* pTransformA,
							TransformComponent* pTransformB, ForceComponent* pForceA, ForceComponent* pForceB,
							glm::vec3 collisionNormalA, glm::vec3 collisionNormalB)
{
	glm::vec3 velocityA = glm::vec3(0);
	glm::vec3 velocityB = glm::vec3(0);

	float inverseMassA = 0;
	float inverseMassB = 0;

	if (pForceA)
	{
		velocityA = pForceA->GetVelocity();
		inverseMassA = pForceA->GetInverseMass();
	}

	if (pForceB)
	{
		velocityB = pForceB->GetVelocity();
		inverseMassB = pForceB->GetInverseMass();
	}

	// Recalculate velocity based on inverse mass
	if (pCollisionEvent->bodyTypeA == eBodyType::DYNAMIC)
	{
		if (pCollisionEvent->bodyTypeB == eBodyType::STATIC)
		{
			pTransformA->SetOldPosition();
		}

		myutils::ResolveVelocity(velocityA, velocityB, collisionNormalA, pForceA->GetRestitution(),
			inverseMassA, inverseMassB);

		pForceA->SetVelocity(velocityA);
	}

	if (pCollisionEvent->bodyTypeB == eBodyType::DYNAMIC)
	{
		if (pCollisionEvent->bodyTypeA == eBodyType::STATIC)
		{
			pTransformB->SetOldPosition();
		}

		myutils::ResolveVelocity(velocityB, velocityA, collisionNormalB, pForceB->GetRestitution(),
			inverseMassB, inverseMassA);

		pForceB->SetVelocity(velocityB);
	}
}

bool Physics::CheckCollisions(EntityID entityA, std::vector<sCollisionEvent*>& collisionsOut)
{
	bool isIntersecting = false;
	glm::vec3 collisionNormalA = glm::vec3(0);
	glm::vec3 collisionNormalB = glm::vec3(0);
	// Getting all we need from entity A first
	CollisionComponent* pCollA = this->m_pSceneView->GetComponent<CollisionComponent>(entityA, "collision");
	ForceComponent* pForceA = this->m_pSceneView->GetComponent<ForceComponent>(entityA, "force");
	TransformComponent* pTransformA = this->m_pSceneView->GetComponent<TransformComponent>(entityA, "transform");
	if (!pCollA || !pTransformA 
		|| pCollA->Get_eBodyType() == eBodyType::STATIC
		|| !pCollA->IsActive())
	{
		// Entity don't have components to collide
		return false;
	}

	// Go through each other collidable object
	for (this->m_pSceneView->First("collision"); !this->m_pSceneView->IsDone(); this->m_pSceneView->Next())
	{
		EntityID entityB = this->m_pSceneView->CurrentKey();
		sCollisionEvent* pCollisionEvent = new sCollisionEvent();
		CollisionComponent* pCollB = this->m_pSceneView->CurrentValue<CollisionComponent>();
		TransformComponent* pTransformB = this->m_pSceneView->GetComponent<TransformComponent>(entityB, "transform");
		ForceComponent* pForceB = this->m_pSceneView->GetComponent<ForceComponent>(entityB, "force");
		if (!pCollB
			|| this->m_pSceneView->CurrentKey() == entityA // Check its not the same object
			|| this->IsAlreadyTested(entityA, entityB) // Check has already been tested this frame
			|| !pCollB->IsActive()
			)
		{
			continue;
		}

		pCollisionEvent->entityA = entityA;
		pCollisionEvent->entityB = entityB;

		this->m_vecFrameCollisionsVisited.push_back(pCollisionEvent);

		// TODO: Better structure and strategy for these tests

		// Check collision type (Sphere x Triangle mesh, Sphere x Sphere ...)
		// Check collision type intersection test
		if (pCollA->Get_eShape() == eShape::SPHERE)
		{
			sSphere* pSphereA = pCollA->GetShape<sSphere>();

			if (pCollB->Get_eShape() == eShape::SPHERE)
			{
  				sSphere* pSphereB = pCollB->GetShape<sSphere>();

				bool isCollision = this->SphereSphere_Test(pSphereA, pTransformA, pSphereB, pTransformB,
					pCollisionEvent);

				if (!isCollision)
				{
					continue;
				}
				// Normals for the new velocity calculation
				collisionNormalA = myutils::GetNormal(pCollisionEvent->contactPointB, pTransformB->GetPosition());
				collisionNormalB = myutils::GetNormal(pCollisionEvent->contactPointA, pTransformA->GetPosition());

				pCollisionEvent->reflectionNormalA = myutils::GetReflectionNormal(pCollisionEvent->contactPointA,
					pForceA->GetVelocity(), pTransformB->GetPosition());
				pCollisionEvent->reflectionNormalB = myutils::GetReflectionNormal(pCollisionEvent->contactPointB,
					pForceB->GetVelocity(), pTransformA->GetPosition());
			}
			else if (pCollB->Get_eShape() == eShape::MESH_OF_TRIANGLES_INDIRECT)
			{
				// Get All we need for entity B test
				ModelComponent* pModelB = this->m_pSceneView->GetComponent<ModelComponent>(entityB, "model");
				if (!pModelB)
				{
					continue;
				}
				sMesh* pMeshB = pModelB->pMeshInfo;
				ForceComponent* pForceB = this->m_pSceneView->GetComponent<ForceComponent>(entityB, "force");
				if (!pMeshB || !pTransformB)
				{
					continue;
				}

				bool isCollision = this->SphereTriMeshIndirect_Test(pSphereA, pTransformA,
					pMeshB, pTransformB, pCollisionEvent);
				if (!isCollision)
				{
					continue;
				}

				// Normals for the new velocity calculations
				collisionNormalA = myutils::GetNormal(pCollisionEvent->pMeshTriangleCollision->vertices);

				pCollisionEvent->reflectionNormalA = myutils::GetReflectionNormal(pForceA->GetVelocity(), pCollisionEvent->pMeshTriangleCollision->vertices);
			}
			else
			{
				// Not implemented shape
				continue;
			}
		}
		else if (pCollA->Get_eShape() == eShape::AABB)
		{
			sAABB* pAABB_A = pCollA->GetShape<sAABB>();

			if (pCollB->Get_eShape() == eShape::GRID)
			{
				sGrid* pGridB = pCollB->GetShape<sGrid>();
				bool isCollision = this->AABBGrid_Test(pAABB_A, pTransformA, pGridB, pTransformB, pCollisionEvent);

				if (!isCollision)
				{
					continue;
				}
			}
			else if (pCollB->Get_eShape() == eShape::AABB)
			{
				sAABB* pAABBB_B = pCollB->GetShape<sAABB>();
				bool isCollision = this->AABBAABB_Test(pAABB_A, pTransformA, pAABBB_B, pTransformB, pCollisionEvent);

				if (!isCollision)
				{
					continue;
				}
			}
			else
			{
				// Not implemented test
				continue;
			}
		}
		else
		{
			// Not implemented shape for component A
			// Can return right away
			return false;
		}

		if (!pCollisionEvent)
		{
			continue;
		}

		isIntersecting = true;

		pCollisionEvent->bodyTypeA = pCollA->Get_eBodyType();
		pCollisionEvent->bodyTypeB = pCollB->Get_eBodyType();

		this->ResolveCollision(pCollisionEvent, pTransformA, pTransformB, pForceA, pForceB, 
								collisionNormalA, collisionNormalB);

		collisionsOut.push_back(pCollisionEvent);
	}

	return isIntersecting;
}

bool Physics::CheckCollisions(EntityID entityA)
{
	return this->CheckCollisions(entityA, this->m_vecFrameCollisions);
}

bool Physics::IsAlreadyTested(EntityID entityA, EntityID entityB)
{
	for (sCollisionEvent* pCollisionTest : this->m_vecFrameCollisionsVisited)
	{
		if ((pCollisionTest->entityA == entityA && pCollisionTest->entityB == entityB)
			|| (pCollisionTest->entityA == entityB && pCollisionTest->entityB == entityA))
		{
			return true;
		}
	}

	return false;
}

void Physics::NewFrame()
{
	// TODO: Reestructure so we don't have this mess of pointers 
	// Clear all collisions and its respective triangles from last frame
	for (sCollisionEvent* pCollision : this->m_vecFrameCollisionsVisited)
	{
		if (pCollision->pMeshTriangleCollision)
		{
			delete pCollision->pMeshTriangleCollision;
		}
		delete pCollision;
	}
	this->m_vecFrameCollisionsVisited.clear();
	this->m_vecFrameCollisions.clear();
}

void Physics::Update(EntityID entityID, double deltaTime)
{
	if (!this->m_isRunning)
	{
		return;
	}

	this->ApplyForce(entityID, deltaTime);

	bool isColliding = this->CheckCollisions(entityID);

	if (!isColliding)
	{
		return;
	}

	// Trigger collision event for objects that collided
	this->m_pCollisionEvent->TriggerCollisions(this->m_vecFrameCollisions);
}

bool Physics::IsRunning()
{
	return this->m_isRunning;
}

void Physics::SetRunning(bool isRunning)
{
	this->m_isRunning = isRunning;
}

// TODO: Remove code repetition and reestructure this whole shape thing

bool Physics::SphereTriMeshIndirect_Test(sSphere* pSphere, TransformComponent* pTransformSphere,
												sMesh* pMesh, TransformComponent* pTransformMesh,
												sCollisionEvent* pCollision)
{
	float closestDistanceSoFar = FLT_MAX;
	glm::vec3 closestTriangleVertices[3] = { glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) };
	glm::vec3 closestContactPoint = glm::vec3(0.0f);
	unsigned int indexOfClosestTriangle = INT_MAX;

	// Which triangle is closest to this sphere (right now)
	for (unsigned int index = 0; index != pMesh->numberOfIndices; index += 3)
	{
		glm::vec3 verts[3];

		// Get triangle vertices
		verts[0].x = pMesh->pVertices[pMesh->pIndices[index]].x;
		verts[0].y = pMesh->pVertices[pMesh->pIndices[index]].y;
		verts[0].z = pMesh->pVertices[pMesh->pIndices[index]].z;

		verts[1].x = pMesh->pVertices[pMesh->pIndices[index + 1]].x;
		verts[1].y = pMesh->pVertices[pMesh->pIndices[index + 1]].y;
		verts[1].z = pMesh->pVertices[pMesh->pIndices[index + 1]].z;

		verts[2].x = pMesh->pVertices[pMesh->pIndices[index + 2]].x;
		verts[2].y = pMesh->pVertices[pMesh->pIndices[index + 2]].y;
		verts[2].z = pMesh->pVertices[pMesh->pIndices[index + 2]].z;

		// Transform this object in world space
		glm::mat4 matModel = glm::mat4(1.0f);
		myutils::ApplyTransformInModelMat(pTransformMesh, matModel);

		glm::vec4 vertsWorld[3];
		vertsWorld[0] = (matModel * glm::vec4(verts[0], 1.0f));
		vertsWorld[1] = (matModel * glm::vec4(verts[1], 1.0f));
		vertsWorld[2] = (matModel * glm::vec4(verts[2], 1.0f));

		// Getting closest point in triangle
		glm::vec3 thisTriangleClosestPoint = myutils::ClosestPtPointTriangle(pTransformSphere->GetPosition(),
												vertsWorld[0], vertsWorld[1], vertsWorld[2]);

		// Is this the closest so far
		float distanceToThisTriangle = glm::distance(thisTriangleClosestPoint, pTransformSphere->GetPosition());
		if (distanceToThisTriangle > closestDistanceSoFar)
		{
			continue;
		}

		// this one is closer
		closestDistanceSoFar = distanceToThisTriangle;
		// Make note of the triangle index
		indexOfClosestTriangle = index;
		// 
		closestTriangleVertices[0] = vertsWorld[0];
		closestTriangleVertices[1] = vertsWorld[1];
		closestTriangleVertices[2] = vertsWorld[2];

		closestContactPoint = thisTriangleClosestPoint;

	} //for ( unsigned int index...

	// Hit the triangle?
	if (closestDistanceSoFar > pSphere->radius)
	{
		// no
		return false;
	}

	// Return this with all the collision info
	// The collision event is responsible for deleting it
	pCollision->pMeshTriangleCollision = new sTriangle(closestTriangleVertices);
	pCollision->contactPointA = closestContactPoint;

	return true;
}

// From: Real-Time Collision Detection- Ericson, Christer
// Chapter 4:
bool Physics::SphereSphere_Test(sSphere* pSphereA, TransformComponent* pTransformA, 
											sSphere* pSphereB, TransformComponent* pTransformB,
											sCollisionEvent* pCollision)
{
	// Calculate squared distance between centers
	glm::vec3 d = pTransformA->GetPosition() - pTransformB->GetPosition();
	float dist2 = glm::dot(d, d);
	// Spheres intersect if squared distance is less than squared sum of radii
	float radiusSum = pSphereA->radius + pSphereB->radius;
	if (dist2 > radiusSum * radiusSum)
	{
		// Not hit
		return false;
	}

	// Return this with all the collision info
	// The collision event is responsible for deleting it
	pCollision->contactPointA = myutils::GetSpheresContactPont(pTransformA->GetPosition(), pSphereA->radius, 
															pTransformB->GetPosition(), pSphereB->radius);
	pCollision->contactPointB = myutils::GetSpheresContactPont(pTransformB->GetPosition(), pSphereB->radius,
															pTransformA->GetPosition(), pSphereA->radius);

	return pCollision;
}

// Function to check for AABB-grid intersection
bool Physics::AABBGrid_Test(sAABB* aabb, TransformComponent* pTransformAABB,
	sGrid* grid, TransformComponent* pTransformGrid,
	sCollisionEvent* pCollision)
{
	// Transform objects in world space
	glm::mat4 matModel = glm::mat4(1.0f);
	myutils::ApplyTransformInModelMat(pTransformAABB, matModel);

	glm::vec4 minWorld = (matModel * glm::vec4(aabb->minXYZ, 1.0f));
	glm::vec4 maxWorld = (matModel * glm::vec4(aabb->maxXYZ, 1.0f));

	// Check if objects collide
	bool isIntersect = false;
	for (int i = 0; i < grid->vecGrid.size(); ++i)
	{
		// if this position is between min and max from aabb
		glm::vec3 worldPosition = grid->vecGrid[i];
		if (minWorld.x <= worldPosition.x && maxWorld.x >= worldPosition.x &&
			minWorld.y <= worldPosition.y && maxWorld.y >= worldPosition.y)
		{
			pCollision->contactPointA = worldPosition;
			pCollision->contactPointB = worldPosition;

			return true; // Collision detected
		}
	}

	return false;
}

// From: Real-Time Collision Detection- Ericson, Christer
// Chapter 4:
bool Physics::AABBAABB_Test(sAABB* aabbA, TransformComponent* pTransformA,
	sAABB* aabbB, TransformComponent* pTransformB,
	sCollisionEvent* pCollision)
{
	// Transform A in world space
	glm::mat4 matModelA = glm::mat4(1.0f);
	myutils::ApplyTransformInModelMat(pTransformA, matModelA);
	glm::vec4 AminWorld = (matModelA * glm::vec4(aabbA->minXYZ, 1.0f));
	glm::vec4 AmaxWorld = (matModelA * glm::vec4(aabbA->maxXYZ, 1.0f));

	// Transform B in world space
	glm::mat4 matModelB = glm::mat4(1.0f);
	myutils::ApplyTransformInModelMat(pTransformB, matModelB);
	glm::vec4 BminWorld = (matModelB * glm::vec4(aabbB->minXYZ, 1.0f));
	glm::vec4 BmaxWorld = (matModelB * glm::vec4(aabbB->maxXYZ, 1.0f));

	// Check if objects collide
	if (AmaxWorld[0] < BminWorld[0] || AminWorld[0] > BmaxWorld[0]
		|| AmaxWorld[1] < BminWorld[1] || AminWorld[1] > BmaxWorld[1]
		|| AmaxWorld[2] < BminWorld[2] || AminWorld[2] > BmaxWorld[2])
	{
		return false;
	}
	pCollision->contactPointA = AminWorld;
	pCollision->contactPointB = BminWorld;

	return true;
}