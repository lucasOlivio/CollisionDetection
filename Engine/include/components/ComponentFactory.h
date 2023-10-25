#pragma once

#include "iComponent.h"
#include <string>

class ComponentFactory
{
public:
	static iComponent* CreateComponent(std::string componentName);
};