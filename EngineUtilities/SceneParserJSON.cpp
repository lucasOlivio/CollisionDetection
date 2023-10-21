#include "SceneParserJSON.h"
#include "common/components.h"
#include "ParserJSON.h"

SceneParserJSON::SceneParserJSON()
{
}

SceneParserJSON::~SceneParserJSON()
{
}

bool SceneParserJSON::Parse(rapidjson::Value& jsonObject, myecs::sScene* pScene)
{
    using namespace rapidjson;
    using namespace myecs;

    bool isValid = jsonObject.IsArray();
    if (!isValid)
    {
        printf("Error: File not valid, expected array of entities!\n");
        return false;
    }

    ParserJSON parser = ParserJSON();

    // Go over each entity
    for (uint entity = 0; entity < jsonObject.Size(); entity++) {
        Value& entityObject = jsonObject[entity];
        bool isValid = entityObject.IsObject();
        if (!isValid)
        {
            printf("Error: Entity #%d not valid, expected object of components!\n", entity);
            return false;
        }
        
        // Inside entity iterate over each component
        for (Value::ConstMemberIterator entityMember = entityObject.MemberBegin(); entityMember != entityObject.MemberEnd(); ++entityMember) {
            std::string componentName = entityMember->name.GetString();
            Value& componentObject = jsonObject[entity][entityMember->name];
            bool isValid = componentObject.IsObject();
            if (!isValid)
            {
                printf("Error: Entity #%d not valid, expected object of components!\n", entity);
                return false;
            }

            // Foe every specific component we must parse to the expected structure 
            // them put in respective map
            bool isParsed = true;
            if (entityMember->name == "transform") 
            {
                sTransformComponent transform;

                isParsed &= parser.GetVec4(componentObject["position"], transform.position);
                isParsed &= parser.GetVec4(componentObject["orientation"], transform.position);
                isParsed &= parser.GetFloat(componentObject["scale"], transform.scale);

                pScene->transforms[entity] = transform;
            }
            else if (entityMember->name == "model") 
            {
                sModelComponent model;

                isParsed &= parser.GetString(componentObject["name"], model.name);
                isParsed &= parser.GetString(componentObject["friendlyName"], model.friendlyName);
                isParsed &= parser.GetBool(componentObject["isWireframe"], model.isWireframe);
                isParsed &= parser.GetBool(componentObject["doNotLight"], model.doNotLight);

                pScene->models[entity] = model;
            }
            else if (entityMember->name == "camera") 
            {
                sCameraComponent camera;

                isParsed &= parser.GetVec3(componentObject["cameraEye"], camera.cameraEye);
                isParsed &= parser.GetVec3(componentObject["cameraTarget"], camera.cameraTarget);
                isParsed &= parser.GetVec3(componentObject["upVector"], camera.upVector);

                pScene->cameras[entity] = camera;
            }
            else
            {
                printf("Error: component %s doesn't exists!", componentName.c_str());
                continue;
            }

            if (!isParsed)
            {
                printf("Error parsing component '%s' from entity #%d", componentName.c_str(), entity);
                return false;
            }
        }
    }

    return true;
}
