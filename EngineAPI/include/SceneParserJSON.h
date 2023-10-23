#pragma once

#include "scene/iScene.h"
#include <string>
#include <rapidjson/document.h>

class SceneParserJSON
{
public:
	SceneParserJSON();
	~SceneParserJSON();

	bool Parse(rapidjson::Value& jsonObject, iScene* pScene);
};