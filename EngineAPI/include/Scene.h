#pragma once

#include <map>
#include <string>
#include "types.h"
#include "components.h"

namespace engine
{
	class Scene
	{
	private:
		EntityID m_numEntities;

		std::map<EntityID, TransformComponent> m_transforms;
		std::map<EntityID, ModelComponent> m_models;
		std::map<EntityID, CameraComponent> m_cameras;
	public:
		Scene();
		~Scene();

		EntityID GetNumEntities();

		EntityID CreateEntity();

		bool GetTransform(EntityID entityID, TransformComponent& transform);
		void SetTransform(EntityID entityID, TransformComponent transform);

		void GetModels(std::map<EntityID, ModelComponent>& models);
		bool GetModel(EntityID entityID, ModelComponent& model);
		void SetModel(EntityID entityID, ModelComponent model);

		void GetCameras(std::map<EntityID, CameraComponent>& cameras);
		bool GetCamera(EntityID entityID, CameraComponent& camera);
		void SetCamera(EntityID entityID, CameraComponent camera);
	};
}