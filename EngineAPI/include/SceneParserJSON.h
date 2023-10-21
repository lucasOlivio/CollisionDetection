#pragma once
#include "common/scene.h"
#include <string>
#include <rapidjson/document.h>

class SceneParserJSON
{
public:
	SceneParserJSON();
	~SceneParserJSON();

	bool Parse(rapidjson::Value& jsonObject, myecs::sScene* pScene);
};