#pragma once

#include "drawInfo.h"
#include "iShaderMediator.h"
#include <string>
#include <map>

class VAOManager
{
private:
	iShaderMediator* m_pShaderMediator;

	std::string m_basePath;
	std::map< std::string    /*model name*/,
		      engine::sMesh* /* info needed to draw*/ >
		      m_mapModelNameToMesh;

	bool m_LoadTheFile_Ply_XYZ_N_RGBA(std::string theFileName, engine::sMesh* drawInfo);
public:
	VAOManager(iShaderMediator* pShaderMediator);
	~VAOManager();

	void Destroy();
	void DestroyVBO(std::string modelName);

	bool LoadModelIntoVAO(std::string& fileName, std::string& shaderProgram, bool bIsDynamicBuffer);

	bool UpdateVAOBuffers(std::string& fileName,
						  std::string& shaderProgram,
						  engine::sMesh* pUpdatedMesh);

	engine::sMesh* FindMeshByModelName(std::string& filename);

	void SetBasePath(std::string basePath);
};

