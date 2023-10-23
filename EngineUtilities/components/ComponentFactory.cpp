#include "components/ComponentFactory.h"
#include "components.h"

iComponent* ComponentFactory::CreateComponent(std::string componentName)
{
	iComponent* newComponent = nullptr;

	if (componentName == "model")
	{
		newComponent = new ModelComponent();
	}
	else if (componentName == "transform")
	{
		newComponent = new TransformComponent();
	}
	else if (componentName == "camera")
	{
		newComponent = new CameraComponent();
	}
	else
	{
		printf("Error: Invalid component '%s'\n", componentName.c_str());
	}

	return newComponent;
}
