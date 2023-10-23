#include "scene/Scene.h"

Scene::Scene()
{
    this->m_numEntities = 0;
    this->m_components.clear();
}

Scene::~Scene()
{
    this->m_components.clear();
}

void Scene::Destroy()
{
    for (auto& pairComponent : this->m_components) {
        for (auto& pairEntityComp : pairComponent.second) {
            delete pairEntityComp.second;
        }
        pairComponent.second.clear();
    }
    this->m_components.clear(); // Optional: Clear the main map
}

EntityID Scene::GetNumEntities()
{
    return this->m_numEntities;
}

EntityID Scene::CreateEntity()
{
    EntityID newEntityID = this->m_numEntities;
    this->m_numEntities++;
    return newEntityID;
}

void Scene::DeleteEntity(EntityID entityID)
{
    for (auto& pairComponent : this->m_components) {
        auto& innerMap = pairComponent.second;
        auto entityIter = innerMap.find(entityID);
        if (entityIter != innerMap.end()) {
            delete entityIter->second;
            innerMap.erase(entityIter);
        }
    }
}

void Scene::GetMapComponents(std::string componentName, std::map<EntityID, iComponent*>& componentsOut)
{
    std::map<std::string,
        std::map<EntityID, iComponent*>>::iterator it;
    it = this->m_components.find(componentName);

    if (it == this->m_components.end())
    {
        // No components of this type
        return;
    }

    componentsOut = it->second;
    return;
}

iComponent* Scene::GetComponent(EntityID entityID, std::string componentName)
{
    std::map<EntityID, iComponent*> mapComponents;

    this->GetMapComponents(componentName, mapComponents);

    std::map<EntityID, iComponent*>::iterator it;
    it = mapComponents.find(entityID);

    if (it == mapComponents.end())
    {
        // Entity doesn't have this kind of component
        return nullptr;
    }

    return it->second;
}

void Scene::SetComponent(EntityID entityID, std::string componentName, iComponent* componentIn)
{
    // Check the entity already have this component
    iComponent* compToDelete = this->GetComponent(entityID, componentName);

    // If already have, delete it first
    if (compToDelete)
    {
        delete compToDelete;
    }

    // Now replace with the new component
    this->m_components[componentName][entityID] = componentIn;

    return;
}

std::vector<sComponentInfo> Scene::GetComponentsInfo(EntityID entityID)
{
    std::vector<sComponentInfo> componentsInfo;

    // Go through each component type in the scene
    for (const auto& pairComponents : this->m_components)
    {
        // Check if user has this component
        const auto& itComponents = pairComponents.second.find(entityID);
        if (itComponents == pairComponents.second.end())
        {
            continue;
        }

        // Get info from component and attach to vector
        sComponentInfo componentInfo;
        itComponents->second->GetInfo(componentInfo);

        componentsInfo.push_back(componentInfo);
    }

    return componentsInfo;
}