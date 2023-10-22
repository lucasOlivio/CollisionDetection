#pragma once

#include <string>

namespace engine
{
	class ModelComponent
	{
	public:
		std::string name;
		std::string friendlyName;
		bool isWireframe;
		bool doNotLight;
	};
};