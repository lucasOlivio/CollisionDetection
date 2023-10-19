#pragma once

#include <string>
#include <vector>
#include <map>

class ShaderManager
{
public:
	class Shader {
	public:
		Shader();
		~Shader();
		enum ShaderType
		{
			VERTEX_SHADER,
			FRAGMENT_SHADER,
			UNKNOWN
		};
		ShaderType shaderType;
		std::string GetShaderTypeString(void);

		unsigned int ID;	// or "name" from OpenGL
		std::vector<std::string> vecSource;
		bool isSourceMultiLine;
		std::string fileName;

	};

	class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();
		unsigned int ID;	// ID from OpenGL
		std::string name;	// We give it this name

		// TODO: For the students to do, because it's FUN, FUN, FUN
		std::map< std::string /*name of uniform variable*/,
			int /* uniform location ID */ >
			mapUniformNameToUniformLocation;
		// Returns -1 (just like OpenGL) if NOT found
		int GetUniformIDFromName(std::string name);
		// Look up the uniform location and save it.
		bool LoadUniformLocation(std::string variableName);

	};

	ShaderManager();
	~ShaderManager();

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

private:
	// Returns an empty string if it didn't work
	bool m_LoadSourceFromFile(Shader& shader);
	std::string m_basepath;

	bool m_CompileShaderFromSource(Shader& shader, std::string& error);
	// returns false if no error
	bool m_WasThereACompileError(unsigned int shaderID, std::string& errorText);
	bool m_WasThereALinkError(unsigned int progID, std::string& errorText);

	std::string m_lastError;

	std::map< unsigned int /*ID*/, ShaderProgram > m_IDToShaderProgram;
	std::map< std::string /*name*/, unsigned int /*ID*/ > m_shaderProgramNameToID;
};