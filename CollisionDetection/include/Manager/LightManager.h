#pragma once

#include "Common/OpenGL.h"
#include "Component/Light.h"
#include <vector>

class LightManager
{
private:
	int m_indexSelectedLight;

	std::vector<Light*> m_pLights;

	// Builds the standard file path for the lights
	std::string m_GetLightsFileName(std::string sceneName);
public:
	// ctors dtors
	LightManager();
	~LightManager();

	bool Initialize(std::string sceneName, GLint shaderProgramID);
	void Destroy();

	// Get all light objects
	std::vector<Light*> GetLights();

	// Get specific light object
	Light* GetLight(unsigned int index);

	// Setup all lights in scene
	bool LoadSceneLights(std::string sceneName, GLint shaderProgramID);

	// Save all lights configurations into a file
	bool SaveSceneLightsToFile(std::string sceneName);

	// TODO: Resource should be an interface for all the resources, 
	// so we could move all resources and change parameters in a centralized way through an single point.
	/**
	 * Moving/Changing direction for lights in scene.
	 *
	 * @param axis - Axis where the resource will move (0 - x, 1 - y, 2 - z).
	 * @param orientation - Orientation to move (-1 backwards, 1 forward).
	 * @return Resource was moved or not.
	 */
	bool MoveSelectedLight(unsigned int axis, int orientation);
	bool ChangeDirectionSelectedLight(unsigned int axis, int orientation);

	/**
	 * Changing light type or inner and outer angles for lights in scene.
	 *
	 * @param axis - Axis what param will change (0 - light type, 1 - inner angle, 2 - outer angle).
	 * @param orientation - Orientation to change (-1 backwards, 1 forward).
	 * @return Resource changed or not.
	 */
	bool ChangeParamsSelectedLight(unsigned int axis, int orientation);

	/**
	 * Change lights attenuation in scene.
	 *
	 * @param axis - Which attenuation to change (0 - constant, 1 - linear, 2 - quadratic).
	 * @param orientation - To decrease or increase attenuation (-1 decrease, 1 increase).
	 * @return Resource was changed or not.
	 */
	bool ChangeAttenuationInSelectedLight(unsigned int axis, int orientation);

	// Toggle light status
	bool ToggleSelectedLight();

	// Change to next (1) or previous (-1) light
	void ChangeSelectedLight(int orientation);
};