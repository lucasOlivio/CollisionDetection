#pragma once

#include "scene/iScene.h"
#include "scene/iGameplayDirector.h"
#include "components/iComponent.h"
#include "events/iEvent.h"
#include "common/types.h"
#include <map>
#include <string>

class Scene : public iScene,
			  public iGameplayDirector
{
private:
	EntityID m_numEntities;

	// TODO: For now keep as a map for simplicity, 
	// but later transform into a vector of entities
	// and each entity with a bitmask of components
	std::map<std::string /* component name */,
			 std::map<EntityID, iComponent*>> m_components;

	bool m_isPlaying;

	iEvent* m_pKeyEvents;
	iEvent* m_pCollisionEvents;

	// Components that were already deleted and are waiting end of frame to 
	// be completely removed
	std::vector<iComponent*> m_toDestroy;

public:
	Scene(iEvent* pKeyEvents, iEvent* pCollisionEvents);
	~Scene();

	// Delete all components pointers and clear maps
	virtual void Clear();

	// Delete components that were marked
	void ClearDeleted();

	virtual EntityID GetNumEntities();

	virtual EntityID CreateEntity();
	// Create a new entity id copy of the "entityID" passed
	virtual EntityID CreateEntity(EntityID entityID);
	virtual void DeleteEntity(EntityID entityID);

	// Get all parameters info from all the components
	// this entity has attached to it
	virtual std::vector<sComponentInfo> GetComponentsInfo(EntityID entityID);

	// Get the vector for the respective component
	virtual bool GetMapComponents(std::string componentName, std::map<EntityID, iComponent*>& componentsOut);

	// Get or add a component to/from the scene entity
	virtual iComponent* GetComponent(EntityID entityID, std::string componentName);
	virtual void SetComponent(EntityID entityID, std::string componentName, iComponent* componentIn);

	// Gameplay
	// ------------------------------------------------------------------------------
	virtual void SendAction(std::string action, EntityID entityID, sParameterInfo& parameterIn);

	virtual bool IsPlaying();
	void SetPlaying(bool isPlaying);
};