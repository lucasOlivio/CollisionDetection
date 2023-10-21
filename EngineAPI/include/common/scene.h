#pragma once
#include <map>
#include <string>
#include "common/types.h"
#include "components.h"

namespace myecs
{
	struct sScene
	{
		std::map<uint /*entity id*/, sTransformComponent> transforms;
		std::map<uint /*entity id*/, sModelComponent> models;
		std::map<uint /*entity id*/, sCameraComponent> cameras;
	};
}