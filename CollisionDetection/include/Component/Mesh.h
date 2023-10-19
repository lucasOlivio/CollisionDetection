#pragma once

#include "iTransform.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>

class Mesh :
	public iTransform
{
private:
	glm::vec3 m_position;
	glm::vec3 m_orientation;
	float m_scale;

public:
	// ctors and dtors
	Mesh();
	virtual ~Mesh();

	// Getters
	virtual glm::vec3 GetPosition();
	virtual glm::vec3 GetOrientation();
	float GetScale();

	// Setters
	virtual void SetPosition(glm::vec3 newPosition);
	virtual void SetOrientation(glm::vec3 newOrientation);
	void SetScale(float newScale);

	// Transformations to apply to mesh (Scale, rotate, translate)
	void ApplyTransformations(glm::mat4& matModelParent);

	std::string meshName;
	std::string meshNickname;
	bool isWireframe;
	bool doNotLight;
};