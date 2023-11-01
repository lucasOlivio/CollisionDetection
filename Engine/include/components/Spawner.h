#pragma once

#include <glm/vec3.hpp>
#include "Component.h"

enum eSpawnType
{
    TIMER,
    ACTION
};

class SpawnerComponent : public Component
{
private:
    bool m_isActive;

    eSpawnType m_eSpawnType;

    float m_elapsedTime;
    float m_timer;

    int m_quantity;

    glm::vec3 m_randomAxis;
    glm::vec3 m_randomAmplitude;
public:
    SpawnerComponent();
    virtual ~SpawnerComponent();

	virtual void GetInfo(sComponentInfo& compInfoOut);
	virtual void SetParameter(sParameterInfo& parameterIn);

    void SetActive(bool isActive);
    bool IsActive();

    void Spawn();

    void Update(double deltaTime);
};