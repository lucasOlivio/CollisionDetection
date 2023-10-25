#include "EngineRenderer/ModelSystem.h"
#include "components/iComponent.h"
#include "components/Model.h"
#include "components/Transform.h"
#include "common/opengl.h"
#include "common/utilsMat.h"
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

ModelSystem::ModelSystem(iShaderInfo* pShaderInfo, SceneView* pSceneView)
{
    this->m_pShaderInfo = pShaderInfo;
    this->m_pSceneView = pSceneView;
    this->m_pVAOManager = new VAOManager(this->m_pShaderInfo);
}

ModelSystem::~ModelSystem()
{
    delete this->m_pVAOManager;
}

bool ModelSystem::LoadModels(int shaderID)
{
    for (this->m_pSceneView->First("model"); !this->m_pSceneView->IsDone(); this->m_pSceneView->Next())
    {
        ModelComponent* pModel = this->m_pSceneView->CurrentValue<ModelComponent>();
        // For now only debug objects will need to be dynamic
        pModel->pMeshInfo = this->m_pVAOManager->LoadModelIntoVAO(pModel->name, shaderID, false);
        if (!pModel->pMeshInfo)
        {
            return false;
        }
    }

    return true;
}

bool ModelSystem::LoadModels(std::string basePath, int shaderID)
{
    this->m_pVAOManager->SetBasePath(basePath);

    this->LoadModels(shaderID);

    return true;
}

void ModelSystem::Destroy()
{
    for (this->m_pSceneView->First("model"); !this->m_pSceneView->IsDone(); this->m_pSceneView->Next())
    {
        ModelComponent* pModel = this->m_pSceneView->CurrentValue<ModelComponent>();
        this->m_pVAOManager->DestroyVBO(pModel->name);
    }
}

void ModelSystem::UpdateUL(EntityID entityID, int shaderID)
{
    ModelComponent* pModel = this->m_pSceneView->GetComponent<ModelComponent>(entityID, "model");
    if (!pModel)
    {
        return;
    }

    TransformComponent* pTransformComponent = this->m_pSceneView->GetComponent<TransformComponent>(entityID, "transform");
    if (!pTransformComponent)
    {
        return;
    }

    if (pModel->isWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Set if the mesh should calculate lightning in shader
    GLint doNotLightUL = this->m_pShaderInfo->GetUL(shaderID, "doNotLight");
    glUniform1f(doNotLightUL, pModel->doNotLight);

    // Update model matrix on shader
    glm::mat4 matModel = glm::mat4(1.0);
    myutils::ApplyTransformInModelMat(pTransformComponent, matModel);
    int matModelUL = this->m_pShaderInfo->GetUL(shaderID, "matModel");
    glUniformMatrix4fv(matModelUL, 1, GL_FALSE, glm::value_ptr(matModel));

    // Also calculate and pass the "inverse transpose" for the model matrix
    glm::mat4 matModelIT = glm::inverse(glm::transpose(matModel));
    int matModelITUL = this->m_pShaderInfo->GetUL(shaderID, "matModel_IT");
    glUniformMatrix4fv(matModelITUL, 1, GL_FALSE, glm::value_ptr(matModelIT));

    return;
}

void ModelSystem::Render(EntityID entityID)
{
    ModelComponent* pModel = this->m_pSceneView->GetComponent<ModelComponent>(entityID, "model");
    if (!pModel)
    {
        return;
    }

    sMesh* pMesh = this->m_pVAOManager->FindMeshByModelName(pModel->name);
    if (!pMesh) {
        return;
    }

    // Bind to the VAO and call opengl to draw all vertices
    glBindVertexArray(pMesh->VAO_ID); //  enable VAO (and everything else)
    glDrawElements(GL_TRIANGLES,
                   pMesh->numberOfIndices,
                   GL_UNSIGNED_INT,
                   0);
    glBindVertexArray(0); 			  // disable VAO (and everything else)

    return;
}
