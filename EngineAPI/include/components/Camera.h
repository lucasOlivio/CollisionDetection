#pragma once

#include <glm/vec3.hpp>

namespace engine
{
	class CameraComponent
	{
	public:
		glm::vec3 cameraEye;
		glm::vec3 cameraTarget;
		glm::vec3 upVector;
		bool isActive; // TODO: Only one camera active
	};
};