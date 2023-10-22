#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace engine
{
	class TransformComponent
	{
	private:
		glm::quat m_qOrientation; // Rotation in quaternions
	public:
		glm::vec4 position;
		float scale;

		void SetOrientation(glm::vec4 value);
		// Change orientation by the given amount
		void AdjustOrientation(glm::vec4 value);
		glm::quat GetQuatOrientation();
	};
};