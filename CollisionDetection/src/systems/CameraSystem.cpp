#include "systems/CameraSystem.h"
#include "opengl.h"
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

CameraSystem::CameraSystem(iShaderMediator* pShaderMediator)
{
    this->m_pShaderMediator = pShaderMediator;
}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::UpdateUL(engine::Scene* pScene, std::string& shaderProgram)
{
    using namespace engine;

    std::map<EntityID, CameraComponent> cameras;
    pScene->GetCameras(cameras);

    // Update projection matrix in shader
    for (const std::pair<EntityID, CameraComponent>& camera : cameras)
    {
        const CameraComponent& cameraComponent = camera.second;

        if (!cameraComponent.isActive)
        {
            continue;
        }

        glm::mat4 matView = glm::lookAt(cameraComponent.cameraEye,
                                        cameraComponent.cameraTarget,
                                        cameraComponent.upVector);
        int matViewUL = this->m_pShaderMediator->GetUL(shaderProgram, "matView");
        glUniformMatrix4fv(matViewUL, 1, GL_FALSE, glm::value_ptr(matView));

        return; // We only need one active camera
    }
}
