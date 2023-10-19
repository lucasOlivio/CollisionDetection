#pragma once

#include <glm/vec3.hpp>
#include <string>


class iTransform
{
public:
	virtual ~iTransform() {};

	// Getters
	virtual glm::vec3 GetPosition() = 0;
	virtual glm::vec3 GetOrientation() = 0;

	// Setters
	virtual void SetPosition(glm::vec3 newPosition) = 0;
	virtual void SetOrientation(glm::vec3 newOrientation) = 0;
};