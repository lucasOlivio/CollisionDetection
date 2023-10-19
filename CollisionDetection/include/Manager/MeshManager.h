#pragma once

#include "Common/OpenGL.h"
#include "Manager/VAOManager.h"
#include "Component/Mesh.h"
#include <string>
#include <vector>

class MeshManager
{
private:
	int m_indexSelectedMesh;

	// Smart array of Mesh object
	std::vector<Mesh*> m_pMeshes;

	// Loads all meshes that will be drawn into the scene
	bool m_LoadMeshesFromFile(std::string fileName);

	// Builds the standard file path for the meshes
	std::string m_GetMeshesFileName(std::string sceneName);
public:
	// ctors dtors
	MeshManager();
	~MeshManager();

	bool Initialize(std::string sceneName, GLuint pShaderProgramID,
		VAOManager* pVAOManager);
	void Destroy(VAOManager* pVAOManager);

	// Getters
	std::vector<Mesh*> GetMeshes();

	// Get specific mesh object
	Mesh* GetMesh(unsigned int index);
	Mesh* FindMeshByNickname(std::string nickName);

	// Load all meshes and its data for scene from txt file into VAO using VAOManager
	bool LoadSceneMeshes(std::string sceneName, GLuint pShaderProgramID,
		VAOManager* pVAOManager);

	// Save the scene's meshes configuration to a file
	bool SaveSceneMeshesToFile(std::string sceneName);

	// TODO: Resource should be an interface for all the resources, 
	// so we could move all resources and change parameters in a centralized way through an single point.
	/**
	 * Moving/Rotate/Change scale in scene.
	 *
	 * @param axis - Axis where the resource will move (0 - x, 1 - y, 2 - z).
	 * @param orientation - Orientation to move (-1 backwards, 1 forward).
	 * @return Resource was moved or not.
	 */
	bool MoveSelectedMesh(unsigned int axis, int orientation);
	bool RotateSelectedMesh(unsigned int axis, int orientation);
	bool ChangeScaleSelectedMesh(int orientation);
	void ChangeSelectedMesh(int orientation);
};