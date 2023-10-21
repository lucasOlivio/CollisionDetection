#pragma once

#include "common/drawInfo.h"
#include <string>
#include <map>

class VAOManager
{
private:
	std::string m_basePathWithoutSlash;
	std::map< std::string /*model name*/,
		sMesh* /* info needed to draw*/ >
		m_mapModelNameToVAOID;

	bool m_LoadTheFile_Ply_XYZ_N_RGBA(std::string theFileName, sMesh& drawInfo);
public:
	void DestroyVBO(std::string modelName);

	bool LoadModelIntoVAO(std::string fileName,
		unsigned int shaderProgramID);

	sMesh* FindDrawInfoByModelName(std::string filename);
};

