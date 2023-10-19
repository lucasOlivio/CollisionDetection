#pragma once

#include "Component/ModelInfo.h"
#include <string>
#include <map>

class VAOManager
{
private:
	std::map< std::string /*model name*/,
		ModelDrawInfo* /* info needed to draw*/ >
		m_mapModelNameToVAOID;
public:
	void DestroyVBO(std::string modelName);

	bool LoadModelIntoVAO(std::string fileName,
		unsigned int shaderProgramID);

	ModelDrawInfo* FindDrawInfoByModelName(std::string filename);
};

