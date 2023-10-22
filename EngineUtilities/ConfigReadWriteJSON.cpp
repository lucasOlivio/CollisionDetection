#include "ConfigReadWriteJSON.h"
#include "constants.h"
#include "SceneParserJSON.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

ConfigReadWriteJSON::ConfigReadWriteJSON()
{
}

ConfigReadWriteJSON::~ConfigReadWriteJSON()
{
}

bool ConfigReadWriteJSON::ReadScene(const std::string& filePath, engine::Scene* pScene)
{
    using namespace rapidjson;

    // Load file stream into document object
    FILE* fp = 0;
    fopen_s(&fp, filePath.c_str(), "rb");

    if (!fp)
    {
        printf("File '%s' not found!\n", filePath.c_str());
        return false;
    }

    // TODO: Remove hardcoded value
    char readBuffer[MAX_LINE_LENGTH];
    FileReadStream fs(fp, readBuffer, sizeof(readBuffer));

    Document doc;
    doc.ParseStream(fs);

    fclose(fp);

    // Parse scene and load into structure
    SceneParserJSON sceneParser = SceneParserJSON();
    bool isParsed = sceneParser.Parse(doc, pScene);
    if (!isParsed)
    {
        printf("Error parsing file %s!\n", filePath.c_str());
    }

    return true;
}

bool ConfigReadWriteJSON::WriteScene(const std::string& filePath, engine::Scene* pScene)
{
    return false;
}
