#include "scene/Scene.h"
#include "components.h"
#include "components/ComponentBuilder.h"

Scene::Scene(iEvent* pKeyEvents, iEvent* pCollisionEvents)
{
    this->m_isPlaying = false;
    this->m_pKeyEvents = pKeyEvents;
    this->m_pCollisionEvents = pCollisionEvents;
    this->m_numEntities = 0;
    this->m_components.clear();
    this->m_toDestroy.clear();
}

Scene::~Scene()
{
    this->m_components.clear();
}

void Scene::Clear()
{
    for (auto& pairComponent : this->m_components) {
        for (auto& pairEntityComp : pairComponent.second) {
            Component* pComp = (Component*)pairEntityComp.second;
            this->m_pKeyEvents->Dettach(pComp);
            this->m_pCollisionEvents->Dettach(pComp);
            pComp->SetDeleted(true);
            this->m_toDestroy.push_back(pairEntityComp.second) ;
        }
        pairComponent.second.clear();
    }
    this->m_components.clear();
    this->m_numEntities = 0;
}

void Scene::ClearDeleted()
{
    for (iComponent* pComp : this->m_toDestroy)
    {
        delete pComp;
    }
    this->m_toDestroy.clear();
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

EntityID Scene::CreateEntity(EntityID entityID)
{
    EntityID newEntityID = this->CreateEntity();
    
    std::vector<sComponentInfo> componentsInfo = this->GetComponentsInfo(entityID);

    ComponentBuilder compBuilder = ComponentBuilder(this);
    for (sComponentInfo sCompInfo : componentsInfo)
    {
        if (sCompInfo.componentName == "player")
        {
            continue;
        }

        iComponent* pNewComp = compBuilder.BuildComponent(sCompInfo, newEntityID);

        if (sCompInfo.componentName == "model")
        {
            ModelComponent* pNewModelComp = (ModelComponent*)pNewComp;
            ModelComponent* pModelComp = (ModelComponent*)this->GetComponent(entityID, "model");
            pNewModelComp->pMeshInfo = pModelComp->pMeshInfo;
        }
    }

    return newEntityID;
}

void Scene::DeleteEntity(EntityID entityID)
{
    for (auto& pairComponent : this->m_components) {
        auto& innerMap = pairComponent.second;
        auto entityIter = innerMap.find(entityID);
        if (entityIter != innerMap.end()) {
            Component* pComp = (Component*)entityIter->second;
            this->m_pKeyEvents->Dettach(pComp);
            this->m_pCollisionEvents->Dettach(pComp);
            pComp->SetDeleted(true);
            this->m_toDestroy.push_back(pComp);
            innerMap.erase(entityIter);
        }
    }
}

bool Scene::GetMapComponents(std::string componentName, std::map<EntityID, iComponent*>& componentsOut)
{
    std::map<std::string,
        std::map<EntityID, iComponent*>>::iterator it;
    it = this->m_components.find(componentName);

    if (it == this->m_components.end())
    {
        // No components of this type
        return false;
    }

    componentsOut = it->second;
    return true;
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
    Component* compToDelete = (Component*)this->GetComponent(entityID, componentName);

    // If already have, delete it first
    if (compToDelete)
    {
        compToDelete->SetDeleted(true);
        this->m_toDestroy.push_back(compToDelete);
    }

    // Now replace with the new component
    this->m_components[componentName][entityID] = componentIn;
    componentIn->SetGameplayDirector(this);

    if (!this->IsPlaying())
    {
        return;
    }

    if (componentName == "player")
    {
        PlayerComponent* pPlayer = (PlayerComponent*)componentIn;
        this->m_pKeyEvents->Attach(pPlayer);
        pPlayer->SetPlaying(this->IsPlaying());
    }

    if (componentName == "collision")
    {
        CollisionComponent* pCollision = (CollisionComponent*)componentIn;
        this->m_pCollisionEvents->Attach(pCollision);
    }

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

void Scene::SendAction(std::string action, EntityID entityID, sParameterInfo& parameterIn)
{
    if (action == "shoot")
    {
        EntityID newEntityID = this->CreateEntity(entityID);

        TransformComponent* pTransform = (TransformComponent*)this->GetComponent(newEntityID, "transform");
        if (pTransform)
        {
            glm::vec3 newPosition = glm::vec3(parameterIn.parameterFloatValue, 0, 0);
            pTransform->Move(newPosition);
        }

        ForceComponent* pForce = (ForceComponent*)this->GetComponent(newEntityID, "force");
        if (pForce)
        {
            pForce->SetActive(true);
            pForce->SetVelocity(parameterIn.parameterVec3Value);
            pForce->SetAcceleration(parameterIn.parameterVec4Value);
        }

        CollisionComponent* pCollision = (CollisionComponent*)this->GetComponent(newEntityID, "collision");
        if (pCollision)
        {
            pCollision->SetActive(true);
        }
    }
    else if (action == "destroy")
    {
        this->DeleteEntity(entityID);
    }

    return;
}

bool Scene::IsPlaying()
{
    if (this->m_isPlaying)
    {
        return true;
    } 
    else
    {
        return false;
    }
}

void Scene::SetPlaying(bool isPlaying)
{
    this->m_isPlaying = isPlaying;

    if (!this->m_isPlaying)
    {

    }
}
