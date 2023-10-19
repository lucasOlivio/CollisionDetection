#include "Common/OpenGL.h"
#include "Component/Light.h"
#include <string>

// ctors dtors
Light::Light(int i)
{
	this->m_name = "light"+std::to_string(i);
	this->m_position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);     // Center of everything
	this->m_diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);		// White color
	this->m_specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);     // White light
	this->m_atten = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);		// No attenuation
	this->m_direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);	// Defaults to straight down
	this->m_params = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);	    // LIGHT_TYPE POINT
	this->m_status = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);	    // Off

	this->m_position_UL = -1;
	this->m_diffuse_UL = -1;
	this->m_specular_UL = -1;
	this->m_atten_UL = -1;
	this->m_direction_UL = -1;
	this->m_params_UL = -1;
	this->m_status_UL = -1;
}

Light::~Light()
{
}

// Set uniforms locations from register (only needed once, only in the start so it doesn't consume much time)
void Light::m_SetULs(GLint shaderProgramID, std::string ulBasePath)
{
	// Set dot for base path, the light must be a structure inside the shader so we can set all the parameters
	if (ulBasePath.back() != '.')
	{
		ulBasePath += ".";
	}
	this->m_position_UL = glGetUniformLocation(shaderProgramID, (ulBasePath + "position").c_str());
	this->m_diffuse_UL = glGetUniformLocation(shaderProgramID, (ulBasePath + "diffuse").c_str());
	this->m_specular_UL = glGetUniformLocation(shaderProgramID, (ulBasePath + "specular").c_str());
	this->m_atten_UL = glGetUniformLocation(shaderProgramID, (ulBasePath + "atten").c_str());
	this->m_direction_UL = glGetUniformLocation(shaderProgramID, (ulBasePath + "direction").c_str());
	this->m_params_UL = glGetUniformLocation(shaderProgramID, (ulBasePath + "params").c_str());
	this->m_status_UL = glGetUniformLocation(shaderProgramID, (ulBasePath + "status").c_str());
}

// Setup the UL locations and all light configurations
void Light::SetupLight(GLint shaderProgramID, std::string ulBasePath)
{
	this->m_SetULs(shaderProgramID, ulBasePath);
}

std::string Light::GetName()
{
	return this->m_name;
}

// Getters
glm::vec4 Light::GetPosition()
{
	return this->m_position;
}

glm::vec4 Light::GetDiffuse()
{
	return this->m_diffuse;
}

glm::vec4 Light::GetSpecular()
{
	return this->m_specular;
}

glm::vec4 Light::GetAtten()
{
	return this->m_atten;
}

glm::vec4 Light::GetDirection()
{
	return this->m_direction;
}

glm::vec4 Light::GetParams()
{
	return this->m_params;
}

bool Light::GetStatus()
{
	return this->m_status.x;
}

void Light::SetName(std::string name)
{
	this->m_name = name;
	return;
}

// Setters
void Light::SetPosition(glm::vec4 newPosition)
{
	this->m_position = newPosition;

	glUniform4f(this->m_position_UL, this->m_position.x,
		this->m_position.y, this->m_position.z,
		this->m_position.w);
}

void Light::SetDiffuse(glm::vec4 newDiffuse)
{
	this->m_diffuse = newDiffuse;

	glUniform4f(this->m_diffuse_UL, this->m_diffuse.r,
		this->m_diffuse.g, this->m_diffuse.b,
		this->m_diffuse.a);
}

void Light::SetSpecular(glm::vec4 newSpecular)
{
	this->m_specular = newSpecular;

	glUniform4f(this->m_specular_UL, this->m_specular.r,
		this->m_specular.g, this->m_specular.b,
		this->m_specular.a);
}

void Light::SetAtten(glm::vec4 newAtten)
{
	this->m_atten = newAtten;

	glUniform4f(this->m_atten_UL, this->m_atten.x,
		this->m_atten.y, this->m_atten.z,
		this->m_atten.w);
}

void Light::SetDirection(glm::vec4 newDirection)
{
	this->m_direction = newDirection;

	glUniform4f(this->m_direction_UL, this->m_direction.x,
		this->m_direction.y, this->m_direction.z,
		this->m_direction.w);
}

void Light::SetParams(glm::vec4 newParams)
{
	this->m_params = newParams;

	glUniform4f(this->m_params_UL, this->m_params.x,
		this->m_params.y, this->m_params.z,
		this->m_params.w);
}

void Light::SetStatus(bool newStatus)
{
	this->m_status = glm::vec4(newStatus, 0.0f, 0.0f, 0.0f);

	glUniform4f(this->m_status_UL, this->m_status.x,
		this->m_status.y, this->m_status.z,
		this->m_status.w);
}

