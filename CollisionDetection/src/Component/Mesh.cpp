#include "Component/Mesh.h"
#include <glm/gtc/matrix_transform.hpp> 

Mesh::Mesh()
{
    this->m_position = {};
    this->m_orientation = {};
    this->m_scale = 0;
    this->meshName = "";
    this->meshNickname = "";
    this->isWireframe = false;
    this->doNotLight = false;
}

Mesh::~Mesh()
{
}

glm::vec3 Mesh::GetPosition()
{
    return this->m_position;
}

glm::vec3 Mesh::GetOrientation()
{
    return this->m_orientation;
}

float Mesh::GetScale()
{
    return this->m_scale;
}

void Mesh::SetPosition(glm::vec3 newPosition)
{
    this->m_position = newPosition;
}

void Mesh::SetOrientation(glm::vec3 newOrientation)
{
    this->m_orientation = newOrientation;
}

void Mesh::SetScale(float newScale)
{
    this->m_scale = newScale;
}

// Transformations to apply to mesh (Scale, rotate, translate)
void Mesh::ApplyTransformations(glm::mat4& matModelParent) {
    // Translation
    glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f),
        glm::vec3(this->m_position.x,
            this->m_position.y,
            this->m_position.z));

    // Rotation matrix generation
    glm::mat4 matRotateX = glm::rotate(glm::mat4(1.0f),
        this->m_orientation.x, // (float)glfwGetTime(),
        glm::vec3(1.0f, 0.0, 0.0f));

    glm::mat4 matRotateY = glm::rotate(glm::mat4(1.0f),
        this->m_orientation.y, // (float)glfwGetTime(),
        glm::vec3(0.0f, 1.0, 0.0f));

    glm::mat4 matRotateZ = glm::rotate(glm::mat4(1.0f),
        this->m_orientation.z, // (float)glfwGetTime(),
        glm::vec3(0.0f, 0.0, 1.0f));

    // Scaling matrix
    glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
        glm::vec3(this->m_scale,
            this->m_scale,
            this->m_scale));
    //--------------------------------------------------------------

    // Combine all these transformation
    matModelParent = matModelParent * matTranslate;

    matModelParent = matModelParent * matRotateX;
    matModelParent = matModelParent * matRotateY;
    matModelParent = matModelParent * matRotateZ;

    matModelParent = matModelParent * matScale;

    return;
}
