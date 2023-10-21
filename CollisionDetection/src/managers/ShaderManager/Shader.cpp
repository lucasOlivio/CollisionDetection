#include "managers/ShaderManager.h"
#include "common/opengl.h"

ShaderManager::Shader::Shader()
{
	this->ID = 0;
	this->shaderType = Shader::UNKNOWN;
	return;
}

ShaderManager::Shader::~Shader()
{
	return;
}

std::string ShaderManager::Shader::GetShaderTypeString(void)
{
	switch (this->shaderType)
	{
	case Shader::VERTEX_SHADER:
		return "VERTEX_SHADER";
		break;
	case Shader::FRAGMENT_SHADER:
		return "FRAGMENT_SHADER";
		break;
	case Shader::UNKNOWN:
	default:
		return "UNKNOWN_SHADER_TYPE";
		break;
	}
	// Should never reach here...
	return "UNKNOWN_SHADER_TYPE";
}

// Look up the uniform inside the shader, then save it, if it finds it
bool ShaderManager::ShaderProgram::LoadUniformLocation(std::string variableName)
{
	// 
	GLint uniLocation = glGetUniformLocation(this->ID, variableName.c_str());
	// Did it find it (not -1)
	if (uniLocation == -1)
	{	// Nope.
		return false;
	}
	// Save it
	this->m_mapUniformNameToUniformLocation[variableName.c_str()] = uniLocation;

	return true;
}

ShaderManager::ShaderProgram::ShaderProgram()
{
}

ShaderManager::ShaderProgram::~ShaderProgram()
{
}

// Look up the uniform location and save it.
int ShaderManager::ShaderProgram::GetUniformIDFromName(std::string name)
{
	std::map< std::string /*name of uniform variable*/,
		int /* uniform location ID */ >::iterator
		itUniform = this->m_mapUniformNameToUniformLocation.find(name);
	if (itUniform == this->m_mapUniformNameToUniformLocation.end())
	{
		bool ulFound = this->LoadUniformLocation(name);		// Not in map yet, so load to map cache
		if (!ulFound)
		{
			return -1; // OpenGL uniform not found value
		}

		itUniform = this->m_mapUniformNameToUniformLocation.find(name);
	}

	return itUniform->second;		// second if the "int" value
}
