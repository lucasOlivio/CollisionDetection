#include "components/Camera.h"
#include "common/utils.h"
#include <glm/gtx/string_cast.hpp>

void CameraComponent::GetInfo(sComponentInfo& compInfoOut)
{
	using namespace myutils;

	compInfoOut.componentName = "camera";
	compInfoOut.componentParameters.clear();

	this->AddCompParInfo("cameraEye", "vec3", glm::to_string(this->cameraEye), compInfoOut);
	this->AddCompParInfo("cameraTarget", "vec3", glm::to_string(this->cameraTarget), compInfoOut);
	this->AddCompParInfo("upVector", "vec3", glm::to_string(this->upVector), compInfoOut);
	this->AddCompParInfo("isActive", "bool", BoolToString(this->isActive), compInfoOut);
}

void CameraComponent::SetParameter(sParameterInfo& parameterIn)
{
    using namespace myutils;

	if (parameterIn.parameterName == "cameraEye") {
        this->cameraEye = StringToVec3(parameterIn.parameterValue);
    }
    else if (parameterIn.parameterName == "cameraTarget") {
        this->cameraTarget = StringToVec3(parameterIn.parameterValue);
    }
    else if (parameterIn.parameterName == "upVector") {
        this->upVector = StringToVec3(parameterIn.parameterValue);
    }

    return;
}
