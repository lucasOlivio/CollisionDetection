#pragma once
#include "iConfigReadWrite.h"

class ConfigReadWriteJSON : public iConfigReadWrite
{
public:
	ConfigReadWriteJSON();
	virtual ~ConfigReadWriteJSON();

	virtual bool ReadScene(const std::string& filePath, myecs::sScene* pScene);
	virtual bool WriteScene(const std::string& filePath, myecs::sScene* pScene);
};