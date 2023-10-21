#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>

namespace myecs
{
	struct sTransformComponent
	{
		glm::vec4 position;
		glm::vec4 orientation;
		float scale;
	};

	struct sModelComponent
	{
		std::string name;
		std::string friendlyName;

		bool isWireframe;
		bool doNotLight;
	};

	struct sCameraComponent
	{
		glm::vec3 cameraEye;
		glm::vec3 cameraTarget;
		glm::vec3 upVector;
	};
}