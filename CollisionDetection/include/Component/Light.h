#pragma once

#include <glm/vec4.hpp>
#include <string>

class Light
{
private:
	std::string m_name;

	// Light parameters
	glm::vec4 m_position;
	glm::vec4 m_diffuse;	// Colour of the light (used for diffuse)
	glm::vec4 m_specular;	// rgb = highlight colour, w = power
	glm::vec4 m_atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	glm::vec4 m_direction;	// Spot, directional lights
	glm::vec4 m_params;	    // x = Light::LIGHT_TYPE, y = inner angle, z = outer angle, w = TBD
	glm::vec4 m_status;	    // x = 0 for off, 1 for on

	// Parameters uniform locations
	GLint m_position_UL;
	GLint m_diffuse_UL;
	GLint m_specular_UL;
	GLint m_atten_UL;
	GLint m_direction_UL;
	GLint m_params_UL;
	GLint m_status_UL;

	// Set uniforms locations from register (only needed once, only in the start so it doesn't consume much time)
	void m_SetULs(GLint shaderProgramID, std::string ulBasePath);

public:
	enum LIGHT_TYPE {
		POINT,
		SPOT,
		DIRECTIONAL
	};

	// ctors dtors
	Light(int i);
	~Light();

	// Getters
	std::string GetName();
	glm::vec4 GetPosition();
	glm::vec4 GetDiffuse();
	glm::vec4 GetSpecular();
	glm::vec4 GetAtten();
	glm::vec4 GetDirection();
	glm::vec4 GetParams();
	bool GetStatus();

	// Setters
	void SetName(std::string name);
	void SetPosition(glm::vec4 newPosition);
	void SetDiffuse(glm::vec4 newDiffuse);
	void SetSpecular(glm::vec4 newSpecular);
	void SetAtten(glm::vec4 newAtten);
	void SetDirection(glm::vec4 newDirection);
	void SetParams(glm::vec4 newParams);
	void SetStatus(bool newStatus);

	// Setup the UL locations and all light configurations
	void SetupLight(GLint shaderProgramID, std::string ulBasePath);
};