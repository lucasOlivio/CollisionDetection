#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <rapidjson/document.h>

class ParserJSON
{
public:
	ParserJSON();
	~ParserJSON();

	bool GetString(rapidjson::Value& jsonObject, std::string& valueOut);
	bool SetString(rapidjson::Value& jsonObject, const std::string& valueIn, rapidjson::Document::AllocatorType& allocator);

	bool GetFloat(rapidjson::Value& jsonObject, float& valueOut);
	bool SetFloat(rapidjson::Value& jsonObject, float valueIn);

	bool GetInt(rapidjson::Value& jsonObject, int& valueOut);
	bool SetInt(rapidjson::Value& jsonObject, int valueIn);

	bool GetBool(rapidjson::Value& jsonObject, bool& valueOut);
	bool SetBool(rapidjson::Value& jsonObject, bool valueIn);

	bool GetVec4(rapidjson::Value& jsonObject, glm::vec4& valueOut);
	bool SetVec4(rapidjson::Value& jsonObject, const glm::vec4& valueIn);

	bool GetVec3(rapidjson::Value& jsonObject, glm::vec3& valueOut);
	bool SetVec3(rapidjson::Value& jsonObject, const glm::vec3& valueIn);
};