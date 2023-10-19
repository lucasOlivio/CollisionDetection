#include "Common/Global.h"
#include "Manager/LightManager.h"
#include "Common/Utils.h"
#include <fstream>
#include <iostream>

const float LIGHT_MOVEMENT_SPEED = 0.01f;
const float LIGHT_ATTENUATION_SPEED = 0.05f;
const float LIGHT_DIRECTION_SPEED = 1.0f;
const float LIGHT_PARAMS_SPEED = 0.05f;

// Lights file configurations
const std::string KEYWORD_NEW_LIGHT = "***"; // Represents the begining of a new light data bellow
const std::string KEYWORD_LIGHT_NAME = "name:";
const std::string KEYWORD_LIGHT_POSITION = "position:";
const std::string KEYWORD_LIGHT_DIFFUSE = "diffuse:";
const std::string KEYWORD_LIGHT_ATTEN = "atten:";
const std::string KEYWORD_LIGHT_DIRECTION = "direction:";
const std::string KEYWORD_LIGHT_PARAMS = "params:";
const std::string KEYWORD_LIGHT_STATUS = "status:";

// The max number of lights in the scene
const int MAX_NUM_LIGHTS = 40;

// ctors dtors
LightManager::LightManager()
{
    this->m_indexSelectedLight = 0;
}

LightManager::~LightManager()
{
}

bool LightManager::Initialize(std::string sceneName, GLint shaderProgramID)
{
    this->m_pLights.clear();

    // Creates all lights objects for the scene to set the base path from the UL
    for (int index = 0; index < MAX_NUM_LIGHTS; index++)
    {
        std::string ulBasePath = "theLights[" + std::to_string(index) + "].";
        Light* newLight = new Light(index);

        // Sets lights and configuration
        newLight->SetupLight(shaderProgramID, ulBasePath);
        this->m_pLights.push_back(newLight);
    }

    bool lightsLoaded = this->LoadSceneLights(sceneName, shaderProgramID);
    if (!lightsLoaded)
    {
        printf("Error loading lights from file!\n");
        return false;
    }

    if (DEBUG)
    {
        // When debug on we load debug sphere for the light selected

    }

    return true;
}

void LightManager::Destroy()
{
    for (Light* light : this->m_pLights)
    {
        delete light;
    }
    this->m_pLights.clear();
}

std::vector<Light*> LightManager::GetLights()
{
    return this->m_pLights;
}

Light* LightManager::GetLight(unsigned int index)
{
    if (index > this->m_pLights.size())
    {
        std::cout << "Light index bigger than array!" << std::endl;
        return nullptr;
    }
    return this->m_pLights[index];
}

// Builds the standard file path for the lights
std::string LightManager::m_GetLightsFileName(std::string sceneName)
{
    return "assets/database/" + sceneName + "-lights" + ".txt";
}

bool LightManager::LoadSceneLights(std::string sceneName, GLint shaderProgramID)
{
    std::string fileName = this->m_GetLightsFileName(sceneName);
    std::ifstream lightsFile(fileName);
    std::string currString = "";
    // keyword new light is the first command in structure, so we need to start from -1 so the first index will be 0
    int currIndex = -1;
    while (lightsFile >> currString && currIndex < MAX_NUM_LIGHTS) {
        if (currString == KEYWORD_NEW_LIGHT) {
            currIndex += 1;
            continue;
        }
        if (currString == KEYWORD_LIGHT_NAME) {
            std::string name;
            lightsFile >> name;
            this->m_pLights[currIndex]->SetName(name);
            continue;
        }
        if (currString == KEYWORD_LIGHT_POSITION) {
            glm::vec4 position;
            lightsFile >> position.x;
            lightsFile >> position.y;
            lightsFile >> position.z;
            lightsFile >> position.w;
            this->m_pLights[currIndex]->SetPosition(position);
            continue;
        }
        if (currString == KEYWORD_LIGHT_DIFFUSE) {
            glm::vec4 diffuse;
            lightsFile >> diffuse.r; diffuse.r = diffuse.r / 255;
            lightsFile >> diffuse.g; diffuse.g = diffuse.g / 255;
            lightsFile >> diffuse.b; diffuse.b = diffuse.b / 255;
            lightsFile >> diffuse.a; diffuse.a = diffuse.a / 255;
            this->m_pLights[currIndex]->SetDiffuse(diffuse);
            continue;
        }
        if (currString == KEYWORD_LIGHT_ATTEN) {
            glm::vec4 atten;
            lightsFile >> atten.r;
            lightsFile >> atten.g;
            lightsFile >> atten.b;
            lightsFile >> atten.a;
            this->m_pLights[currIndex]->SetAtten(atten);
            continue;
        }
        if (currString == KEYWORD_LIGHT_DIRECTION) {
            glm::vec4 direction;
            lightsFile >> direction.x;
            lightsFile >> direction.y;
            lightsFile >> direction.z;
            lightsFile >> direction.w;
            this->m_pLights[currIndex]->SetDirection(direction);
            continue;
        }
        if (currString == KEYWORD_LIGHT_PARAMS) {
            glm::vec4 params;
            lightsFile >> params.x;
            lightsFile >> params.y;
            lightsFile >> params.z;
            lightsFile >> params.w;
            this->m_pLights[currIndex]->SetParams(params);
            continue;
        }
        if (currString == KEYWORD_LIGHT_STATUS) {
            bool status;
            lightsFile >> status;
            this->m_pLights[currIndex]->SetStatus(status);
            continue;
        }
    }

    return true;
}

bool LightManager::SaveSceneLightsToFile(std::string sceneName)
{
    std::string lightsFileName = this->m_GetLightsFileName(sceneName);

    // "O" for "output" file stream
    std::ofstream lightsFile(lightsFileName.c_str(), std::ofstream::trunc);

    for (unsigned int index = 0; index != this->m_pLights.size(); index++)
    {
        std::string lightName = this->m_pLights[index]->GetName();
        glm::vec4 lightPosition = this->m_pLights[index]->GetPosition();
        glm::vec4 lightDiffuse = this->m_pLights[index]->GetDiffuse();
        glm::vec4 lightAtten = this->m_pLights[index]->GetAtten();
        glm::vec4 lightDirection = this->m_pLights[index]->GetDirection();
        glm::vec4 lightParams = this->m_pLights[index]->GetParams();
        bool lightStatus = this->m_pLights[index]->GetStatus();

        lightsFile << KEYWORD_NEW_LIGHT << std::endl;
        lightsFile << KEYWORD_LIGHT_NAME << " " << lightName << std::endl;
        lightsFile << KEYWORD_LIGHT_POSITION << " " << lightPosition.x << " "
            << lightPosition.y << " "
            << lightPosition.z << " "
            << lightPosition.w << std::endl;
        lightsFile << KEYWORD_LIGHT_DIFFUSE << " " << lightDiffuse.r * 255 << " "
            << lightDiffuse.g * 255 << " "
            << lightDiffuse.b * 255 << " "
            << lightDiffuse.a * 255 << std::endl;
        lightsFile << KEYWORD_LIGHT_ATTEN << " " << lightAtten.r << " "
            << lightAtten.g << " "
            << lightAtten.b << " "
            << lightAtten.a << std::endl;
        lightsFile << KEYWORD_LIGHT_DIRECTION << " " << lightDirection.x << " "
            << lightDirection.y << " "
            << lightDirection.z << " "
            << lightDirection.w << std::endl;
        lightsFile << KEYWORD_LIGHT_PARAMS << " " << lightParams.x << " "
            << lightParams.y << " "
            << lightParams.z << " "
            << lightParams.w << std::endl;
        lightsFile << KEYWORD_LIGHT_STATUS << " " << lightStatus << std::endl;
    }

    std::cout << "Saved succesfully!";

    return true;
}

// Editor controls
// ----------------------------------------------------------------------
bool LightManager::MoveSelectedLight(unsigned int axis, int orientation)
{
    if (axis > 2)
    {
        std::cout << "Axis must be: 0 for x, 1 for y or 2 for z!";
        return false;
    }
    orientation = mymath::Sign(orientation);

    // Change resource new position based on speed and orientation
    Light* pSelectedLight = this->GetLight(this->m_indexSelectedLight);
    glm::vec4 position = pSelectedLight->GetPosition();
    position[axis] += (orientation * LIGHT_MOVEMENT_SPEED);

    // Set new position to resource
    pSelectedLight->SetPosition(position);

    std::cout << "New position: " << position.x << " " << position.y << " " << position.z << std::endl;

    return true;
}

bool LightManager::ChangeDirectionSelectedLight(unsigned int axis, int orientation)
{
    if (axis > 2)
    {
        std::cout << "Axis must be: 0 for x, 1 for y or 2 for z!";
        return false;
    }
    orientation = mymath::Sign(orientation);

    // Change resource new direction based on speed and orientation
    Light* pSelectedLight = this->GetLight(this->m_indexSelectedLight);
    glm::vec4 direction = pSelectedLight->GetDirection();
    direction[axis] += (orientation * LIGHT_DIRECTION_SPEED);

    // Set new position to resource
    pSelectedLight->SetDirection(direction);

    std::cout << "New direction: " << direction.x << " " << direction.y << " " << direction.z << std::endl;

    return true;
}

bool LightManager::ChangeParamsSelectedLight(unsigned int axis, int orientation)
{
    if (axis > 2)
    {
        std::cout << "Axis must be: 0 for light type, 1 for inner angle or 2 for outer angle!";
        return false;
    }
    orientation = mymath::Sign(orientation);

    Light* pSelectedLight = this->GetLight(this->m_indexSelectedLight);
    glm::vec4 params = pSelectedLight->GetParams();

    if (axis == 0)
    {
        // Light type only changes by 1 unit always
        params[0] += (orientation * 1);
        // Light types goes from 0 to 2
        if (params[0] < 0)
        {
            params[0] = 2.0f;
        }
        else if (params[0] > 2)
        {
            params[0] = 0.0f;
        }
    }
    else
    {
        // Change resource new angle based on angle speed % and orientation
        params[axis] *= ((orientation * LIGHT_PARAMS_SPEED) + 1.0f);
    }

    // TODO: Set a min limit of 0.1 and max of 360 for angles
    // Set new angle to resource
    pSelectedLight->SetParams(params);
    std::cout << "New params: " << params.x << " " << params.y << " " << params.z << std::endl;

    return true;
}

bool LightManager::ChangeAttenuationInSelectedLight(unsigned int axis, int orientation)
{
    if (axis > 2)
    {
        std::cout << "Axis must be: 0 for constant, 1 for linear or 2 for quadratic!";
        return false;
    }
    orientation = mymath::Sign(orientation);

    // Change resource new attenuation based on attenuation speed % and orientation
    Light* pSelectedLight = this->GetLight(this->m_indexSelectedLight);
    glm::vec4 atten = pSelectedLight->GetAtten();
    atten[axis] *= ((orientation * LIGHT_ATTENUATION_SPEED) + 1.0f);

    // TODO: Set a min limit of 0.0001 and max of 0.009
    // Set new attenuation to resource
    pSelectedLight->SetAtten(atten);
    std::cout << "New attenuation: " << atten.x << " " << atten.y << " " << atten.z << std::endl;

    return true;
}

bool LightManager::ToggleSelectedLight()
{
    Light* pSelectedLight = this->GetLight(this->m_indexSelectedLight);
    bool status = pSelectedLight->GetStatus();
    pSelectedLight->SetStatus(!status);

    return true;
}

void LightManager::ChangeSelectedLight(int orientation)
{
    orientation = mymath::Sign(orientation);

    this->m_indexSelectedLight += orientation;

    if (this->m_indexSelectedLight >= this->m_pLights.size())
    {
        this->m_indexSelectedLight = 0;
    }
    else if (this->m_indexSelectedLight < 0)
    {
        this->m_indexSelectedLight = this->m_pLights.size() - 1;
    }

    Light* pSelectedLight = this->GetLight(this->m_indexSelectedLight);
    std::string name = pSelectedLight->GetName();
    std::cout << "Selected light: " << name << std::endl;
}
// ----------------------------------------------------------------------