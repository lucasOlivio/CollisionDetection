#include "components/Model.h"
#include "common/utils.h"

void ModelComponent::GetInfo(sComponentInfo& compInfoOut)
{
	using namespace myutils;

	compInfoOut.componentName = "model";
	compInfoOut.componentParameters.clear();

	this->AddCompParInfo("name", "string", this->name, compInfoOut);
	this->AddCompParInfo("friendlyName", "string", this->friendlyName, compInfoOut);
	this->AddCompParInfo("isWireframe", "bool", this->isWireframe, compInfoOut);
	this->AddCompParInfo("doNotLight", "bool", this->doNotLight, compInfoOut);
}

void ModelComponent::SetParameter(sParameterInfo& parameterIn)
{
    using namespace myutils;

    if (parameterIn.parameterName == "name") {
        this->name = parameterIn.parameterStrValue;
    }
    else if (parameterIn.parameterName == "friendlyName") {
        this->friendlyName = parameterIn.parameterStrValue;
    }
    else if (parameterIn.parameterName == "isWireframe") {
        this->isWireframe = parameterIn.parameterBoolValue;
    }
    else if (parameterIn.parameterName == "doNotLight") {
        this->doNotLight = parameterIn.parameterBoolValue;
    }

    return;
}