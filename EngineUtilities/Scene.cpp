#include "Scene.h"
#include "Scene.h"
#include "Scene.h"
#include "Scene.h"
#include "Scene.h"
#include "Scene.h"
#include "Scene.h"
#include "Scene.h"
#include "Scene.h"

engine::Scene::Scene()
{
    this->m_numEntities = 0;
    this->m_cameras.clear();
    this->m_models.clear();
    this->m_transforms.clear();
}

engine::Scene::~Scene()
{
    this->m_cameras.clear();
    this->m_models.clear();
    this->m_transforms.clear();
}

EntityID engine::Scene::GetNumEntities()
{
    return this->m_numEntities;
}

EntityID engine::Scene::CreateEntity()
{
    EntityID newEntityID = this->m_numEntities;
    this->m_numEntities++;
    return newEntityID;
}

bool engine::Scene::GetTransform(EntityID entityID, TransformComponent& transform)
{
    std::map<EntityID, TransformComponent>::iterator it = this->m_transforms.find(entityID);
    if (it == this->m_transforms.end())
    {
        return false;
    }

    transform = it->second;
    return true;
}

void engine::Scene::SetTransform(EntityID entityID, TransformComponent transform)
{
    this->m_transforms[entityID] = transform;
    return;
}

void engine::Scene::GetModels(std::map<EntityID, ModelComponent>& models)
{
    models = this->m_models;
}

bool engine::Scene::GetModel(EntityID entityID, ModelComponent& model)
{
    std::map<EntityID, ModelComponent>::iterator it = this->m_models.find(entityID);
    if (it == this->m_models.end())
    {
        return false;
    }

    model = it->second;
    return true;
}

void engine::Scene::SetModel(EntityID entityID, ModelComponent model)
{
    this->m_models[entityID] = model;
    return;
}

void engine::Scene::GetCameras(std::map<EntityID, CameraComponent>& cameras)
{
    cameras = this->m_cameras;
    return;
}

bool engine::Scene::GetCamera(EntityID entityID, CameraComponent& camera)
{
    std::map<EntityID, CameraComponent>::iterator it = this->m_cameras.find(entityID);
    if (it == this->m_cameras.end())
    {
        return false;
    }

    camera = it->second;
    return true;
}

void engine::Scene::SetCamera(EntityID entityID, CameraComponent camera)
{
    this->m_cameras[entityID] = camera;
    return;
}
