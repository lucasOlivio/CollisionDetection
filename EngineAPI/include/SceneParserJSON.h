#pragma once

#include "scene.h"
#include <string>
#include <rapidjson/document.h>

class SceneParserJSON
{
public:
	SceneParserJSON();
	~SceneParserJSON();

	bool Parse(rapidjson::Value& jsonObject, engine::Scene* pScene);
};