#pragma once

#include "scene.h"
#include <string>

class iConfigReadWrite
{
public:
	virtual ~iConfigReadWrite() {};

	// Load and parse scene from file to the structure
	virtual bool ReadScene(const std::string& filePath, engine::Scene* pScene) = 0;

	// Parse scene from the structure then save to file
	virtual bool WriteScene(const std::string& filePath, engine::Scene* pScene) = 0;
};