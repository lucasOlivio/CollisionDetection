#pragma once

#include "iShaderMediator.h"
#include <string>
#include <vector>
#include <map>

class ShaderManager : public iShaderMediator
{
public:
	class Shader {
	public:
		Shader();
		~Shader();

		unsigned int ID;
		std::vector<std::string> vecSource;
		bool isSourceMultiLine;
		std::string fileName;

		enum ShaderType
		{
			VERTEX_SHADER,
			FRAGMENT_SHADER,
			UNKNOWN
		};
		ShaderType shaderType;

		std::string GetShaderTypeString(void);
	};

	class ShaderProgram {
	private:
		std::map< std::string /*name of uniform variable*/,
			int /* uniform location ID */ >
			m_mapUniformNameToUniformLocation;
	public:
		ShaderProgram();
		~ShaderProgram();
		unsigned int ID;	// ID from OpenGL
		std::string name;	// We give it this name

		// Returns -1 (just like OpenGL) if NOT found
		int GetUniformIDFromName(std::string name);
		// Look up the uniform location and save it.
		bool LoadUniformLocation(std::string variableName);

	};

	ShaderManager(std::string basePath);
	~ShaderManager();

	// Where we initialize all things that could go wrong
	bool AddShaderProgram(std::string shaderProgramName);

	bool UseShaderProgram(unsigned int ID);
	bool UseShaderProgram(std::string shaderProgramName);
	bool CreateProgramFromFile(std::string shaderProgramName,
		Shader& vertexShad,
		Shader& fragShader);
	void SetBasePath(std::string basepath);
	unsigned int GetIDFromShaderProgramName(std::string shaderProgramName);

	// Used to load the uniforms. Returns NULL if not found.
	ShaderProgram* GetShaderProgramFromName(std::string shaderProgramName);

	// Clears last error
	std::string GetLastError(void);

	// Use the shader program name to get the UL
	virtual int GetUL(std::string& shaderProgramName, std::string& ulName);

private:
	bool m_isInitialized;

	// Returns an empty string if it didn't work
	bool m_LoadSourceFromFile(Shader& shader, std::string errorText);
	std::string m_basepath;

	bool m_CompileShaderFromSource(Shader& shader, std::string& error);
	// returns false if no error
	bool m_WasThereACompileError(unsigned int shaderID, std::string& errorText);
	bool m_WasThereALinkError(unsigned int progID, std::string& errorText);

	std::string m_lastError;

	std::map< unsigned int /*ID*/, ShaderProgram > m_IDToShaderProgram;
	std::map< std::string /*name*/, unsigned int /*ID*/ > m_shaderProgramNameToID;
};