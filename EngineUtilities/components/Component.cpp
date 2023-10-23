#include "components/Component.h"

void Component::AddCompParInfo(const std::string& name,
                               const std::string& type,
                               const std::string& value,
                               sComponentInfo& compInfoOut)
{
    sParameterInfo paramInfo;
    paramInfo.parameterName = name;
    paramInfo.parameterType = type;
    paramInfo.parameterValue = value;
    compInfoOut.componentParameters.push_back(paramInfo);

    return;
}
