#include "ParserJSON.h"
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

ParserJSON::ParserJSON()
{
}

ParserJSON::~ParserJSON()
{
}

bool ParserJSON::GetString(rapidjson::Value& jsonObject, std::string& valueOut)
{
    using namespace rapidjson;

    if (jsonObject.IsString()) {
        valueOut = jsonObject.GetString();
        return true;
    }

    return false;
}

bool ParserJSON::SetString(rapidjson::Value& jsonObject, const std::string& valueIn, rapidjson::Document::AllocatorType& allocator)
{
    using namespace rapidjson;

    if (jsonObject.IsString()) {
        jsonObject.SetString(valueIn.c_str(), static_cast<SizeType>(valueIn.length()), allocator);
        return true;
    }

    return false;
}

bool ParserJSON::GetFloat(rapidjson::Value& jsonObject, float& valueOut)
{
    using namespace rapidjson;

    if (jsonObject.IsNumber()) {
        valueOut = jsonObject.GetFloat();
        return true;
    }

    return false;
}

bool ParserJSON::SetFloat(rapidjson::Value& jsonObject, float valueIn)
{
    using namespace rapidjson;

    if (jsonObject.IsNumber()) {
        jsonObject.SetFloat(valueIn);
        return true;
    }

    return false;
}

bool ParserJSON::GetInt(rapidjson::Value& jsonObject, int& valueOut)
{
    using namespace rapidjson;

    if (jsonObject.IsInt()) {
        valueOut = jsonObject.GetInt();
        return true;
    }

    return false;
}

bool ParserJSON::SetInt(rapidjson::Value& jsonObject, int valueIn)
{
    using namespace rapidjson;

    if (jsonObject.IsInt()) {
        jsonObject.SetInt(valueIn);
        return true;
    }

    return false;
}

bool ParserJSON::GetBool(rapidjson::Value& jsonObject, bool& valueOut)
{
    using namespace rapidjson;

    if (jsonObject.IsBool()) {
        valueOut = jsonObject.GetBool();
        return true;
    }

    return false;
}

bool ParserJSON::SetBool(rapidjson::Value& jsonObject, bool valueIn)
{
    using namespace rapidjson;

    if (jsonObject.IsBool()) {
        jsonObject.SetBool(valueIn);
        return true;
    }

    return false;
}

bool ParserJSON::GetVec4(rapidjson::Value& jsonObject, glm::vec4& valueOut)
{
    using namespace rapidjson;

    if (jsonObject.IsArray() && jsonObject.Size() == 4) {
        for (SizeType i = 0; i < jsonObject.Size(); i++) {
            if (!jsonObject[i].IsNumber()) {
                return false;
            }
        }

        valueOut = glm::vec4(
            jsonObject[0].GetFloat(),
            jsonObject[1].GetFloat(),
            jsonObject[2].GetFloat(),
            jsonObject[3].GetFloat()
        );

        return true;
    }

    return false;
}

bool ParserJSON::SetVec4(rapidjson::Value& jsonObject, const glm::vec4& valueIn)
{
    using namespace rapidjson;

    if (jsonObject.IsArray() && jsonObject.Size() == 4) {
        jsonObject[0].SetFloat(valueIn.x);
        jsonObject[1].SetFloat(valueIn.y);
        jsonObject[2].SetFloat(valueIn.z);
        jsonObject[3].SetFloat(valueIn.w);
        return true;
    }

    return false;
}

bool ParserJSON::GetVec3(rapidjson::Value& jsonObject, glm::vec3& valueOut)
{
    using namespace rapidjson;

    if (jsonObject.IsArray() && jsonObject.Size() == 3) {
        for (SizeType i = 0; i < jsonObject.Size(); i++) {
            if (!jsonObject[i].IsNumber()) {
                return false;
            }
        }

        valueOut = glm::vec3(
            jsonObject[0].GetFloat(),
            jsonObject[1].GetFloat(),
            jsonObject[2].GetFloat()
        );

        return true;
    }

    return false;
}

bool ParserJSON::SetVec3(rapidjson::Value& jsonObject, const glm::vec3& valueIn)
{
    using namespace rapidjson;

    if (jsonObject.IsArray() && jsonObject.Size() == 3) {
        jsonObject[0].SetFloat(valueIn.x);
        jsonObject[1].SetFloat(valueIn.y);
        jsonObject[2].SetFloat(valueIn.z);
        return true;
    }

    return false;
}
