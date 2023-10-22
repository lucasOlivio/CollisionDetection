#include "SceneParserJSON.h"
#include "components.h"
#include "ParserJSON.h"

SceneParserJSON::SceneParserJSON()
{
}

SceneParserJSON::~SceneParserJSON()
{
}

bool SceneParserJSON::Parse(rapidjson::Value& jsonObject, engine::Scene* pScene)
{
    using namespace rapidjson;
    using namespace engine;

    bool isValid = jsonObject.IsArray();
    if (!isValid)
    {
        printf("Error: File not valid, expected array of entities!\n");
        return false;
    }

    ParserJSON parser = ParserJSON();

    // Go over each entity
    for (uint entityIndex = 0; entityIndex < jsonObject.Size(); entityIndex++) 
    {
        // This will be our entity ID count, 
        // so we can keep track easily later how many entities we heave
        EntityID entityID = pScene->CreateEntity();

        Value& entityObject = jsonObject[entityIndex];
        bool isValid = entityObject.IsObject();
        if (!isValid)
        {
            printf("Error: Entity #%d not valid, expected object of components!\n", entityIndex);
            return false;
        }
        
        // Inside EntityIDiterate over each component
        for (Value::ConstMemberIterator entityMember = entityObject.MemberBegin(); entityMember != entityObject.MemberEnd(); ++entityMember) 
        {
            std::string componentName = entityMember->name.GetString();
            Value& componentObject = jsonObject[entityIndex][entityMember->name];
            bool isValid = componentObject.IsObject();
            if (!isValid)
            {
                printf("Error: Entity #%d not valid, expected object of components!\n", entityIndex);
                return false;
            }

            // For every specific component we must parse to the expected structure 
            // them put in respective map
            bool isParsed = true;
            if (entityMember->name == "transform") 
            {
                TransformComponent transform;

                isParsed &= parser.GetVec4(componentObject["position"], transform.position);
                isParsed &= parser.GetFloat(componentObject["scale"], transform.scale);
                // Orientation is set using quaternions, so we must use the component to set
                glm::vec4 orientation;
                isParsed &= parser.GetVec4(componentObject["orientation"], orientation);
                transform.SetOrientation(orientation);

                pScene->SetTransform(entityID, transform);
            }
            else if (entityMember->name == "model") 
            {
                ModelComponent model;

                isParsed &= parser.GetString(componentObject["name"], model.name);
                isParsed &= parser.GetString(componentObject["friendlyName"], model.friendlyName);
                isParsed &= parser.GetBool(componentObject["isWireframe"], model.isWireframe);
                isParsed &= parser.GetBool(componentObject["doNotLight"], model.doNotLight);

                pScene->SetModel(entityID, model);
            }
            else if (entityMember->name == "camera") 
            {
                CameraComponent camera;

                isParsed &= parser.GetVec3(componentObject["cameraEye"], camera.cameraEye);
                isParsed &= parser.GetVec3(componentObject["cameraTarget"], camera.cameraTarget);
                isParsed &= parser.GetVec3(componentObject["upVector"], camera.upVector);
                isParsed &= parser.GetBool(componentObject["isActive"], camera.isActive);

                pScene->SetCamera(entityID, camera);
            }
            else
            {
                printf("Error: component %s doesn't exists!", componentName.c_str());
                continue;
            }

            if (!isParsed)
            {
                printf("Error parsing component '%s' from entity #%llu", componentName.c_str(), entityID);
                return false;
            }
        }
    }

    return true;
}
