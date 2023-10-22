#include "systems/TransformSystem.h"
#include "components/Transform.h"
#include "opengl.h"
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

void TransformSystem::m_ApplyTransform(engine::TransformComponent transform, glm::mat4& matModelOut)
{
    // Translation
    glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f),
    glm::vec3(transform.position.x,
              transform.position.y,
              transform.position.z));

    // Rotation matrix generation
    glm::mat4 matRotation = glm::mat4(transform.GetQuatOrientation());

    // Scaling matrix
    glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
    glm::vec3(transform.scale,
              transform.scale,
              transform.scale));
    //--------------------------------------------------------------

    // Combine all these transformation
    matModelOut = matModelOut * matTranslate;

    matModelOut = matModelOut * matRotation;

    matModelOut = matModelOut * matScale;

    return;
}

TransformSystem::TransformSystem(iShaderMediator* pShaderMediator)
{
    this->m_pShaderMediator = pShaderMediator;
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::UpdateUL(EntityID entityID, engine::Scene* pScene, std::string& shaderProgram)
{
    using namespace engine;

    TransformComponent transform;
    bool hasTransform = pScene->GetTransform(entityID, transform);
    if (!hasTransform)
    {
        return;
    }

    // Update model matrix on shader
    glm::mat4 matModel = glm::mat4(1.0);
    this->m_ApplyTransform(transform, matModel);
    int matModelUL = this->m_pShaderMediator->GetUL(shaderProgram, "matModel");
    glUniformMatrix4fv(matModelUL, 1, GL_FALSE, glm::value_ptr(matModel));

    // Also calculate and pass the "inverse transpose" for the model matrix
    glm::mat4 matModelIT = glm::inverse(glm::transpose(matModel));
    int matModelITUL = this->m_pShaderMediator->GetUL(shaderProgram, "matModel_IT");
    glUniformMatrix4fv(matModelITUL, 1, GL_FALSE, glm::value_ptr(matModelIT));
}
