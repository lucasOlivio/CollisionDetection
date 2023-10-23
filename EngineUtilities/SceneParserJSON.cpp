#include "SceneParserJSON.h"
#include "ParserJSON.h"
#include "components.h" // TODO: Get rid of this
#include "components/ComponentFactory.h"

SceneParserJSON::SceneParserJSON()
{
}

SceneParserJSON::~SceneParserJSON()
{
}

bool SceneParserJSON::Parse(rapidjson::Value& jsonObject, iScene* pScene)
{
    using namespace rapidjson;
    

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

            // TODO: Generic way to parse components parameters to remove these horrible dynamic casting
            // 
            // For every specific component we must parse to the expected structure 
            // them put in respective map
            bool isParsed = true;
            iComponent* newComponent = ComponentFactory::CreateComponent(componentName);
            if (componentName == "transform")
            {
                isParsed &= parser.GetVec4(componentObject["position"], 
                                           dynamic_cast<TransformComponent*>(newComponent)->position);
                isParsed &= parser.GetFloat(componentObject["scale"], 
                                            dynamic_cast<TransformComponent*>(newComponent)->scale);

                // Orientation in component is in quaternions, so we must use the component to set
                glm::vec3 orientation;
                isParsed &= parser.GetVec3(componentObject["orientation"], orientation);
                dynamic_cast<TransformComponent*>(newComponent)->SetOrientation(orientation);
            }
            else if (componentName == "model")
            {
                isParsed &= parser.GetString(componentObject["name"], 
                                             dynamic_cast<ModelComponent*>(newComponent)->name);
                isParsed &= parser.GetString(componentObject["friendlyName"], 
                                             dynamic_cast<ModelComponent*>(newComponent)->friendlyName);
                isParsed &= parser.GetBool(componentObject["isWireframe"], 
                                           dynamic_cast<ModelComponent*>(newComponent)->isWireframe);
                isParsed &= parser.GetBool(componentObject["doNotLight"], 
                                           dynamic_cast<ModelComponent*>(newComponent)->doNotLight);
            }
            else if (componentName == "camera")
            {
                isParsed &= parser.GetVec3(componentObject["cameraEye"], 
                                           dynamic_cast<CameraComponent*>(newComponent)->cameraEye);
                isParsed &= parser.GetVec3(componentObject["cameraTarget"], 
                                           dynamic_cast<CameraComponent*>(newComponent)->cameraTarget);
                isParsed &= parser.GetVec3(componentObject["upVector"], 
                                           dynamic_cast<CameraComponent*>(newComponent)->upVector);
                isParsed &= parser.GetBool(componentObject["isActive"], 
                                           dynamic_cast<CameraComponent*>(newComponent)->isActive);
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

            pScene->SetComponent(entityID, componentName, newComponent);
        }
    }

    return true;
}
