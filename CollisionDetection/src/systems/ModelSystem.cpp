#include "systems/ModelSystem.h"
#include "opengl.h"

ModelSystem::ModelSystem(iShaderMediator* pShaderMediator)
{
    this->m_pShaderMediator = pShaderMediator;
    this->m_pVAOManager = new VAOManager(this->m_pShaderMediator);
}

ModelSystem::~ModelSystem()
{
    delete this->m_pVAOManager;
}

bool ModelSystem::Initialize(std::string basePath, std::string& shaderProgram, engine::Scene* pScene)
{
    using namespace engine;
    this->m_pVAOManager->SetBasePath(basePath);

    std::map<EntityID, ModelComponent> models;
    pScene->GetModels(models);
    for (std::pair<EntityID, ModelComponent> model : models)
    {
        // For now only debug objects will need to be dynamic
        this->m_pVAOManager->LoadModelIntoVAO(model.second.name, shaderProgram, false);
    }

    return true;
}

void ModelSystem::Destroy(engine::Scene* pScene)
{
    using namespace engine;

    std::map<EntityID, ModelComponent> models;
    pScene->GetModels(models);
    for (std::pair<EntityID, ModelComponent> model : models)
    {
        this->m_pVAOManager->DestroyVBO(model.second.name);
    }
}

void ModelSystem::UpdateUL(EntityID entityID, engine::Scene* pScene, std::string& shaderProgram)
{
    using namespace engine;

    ModelComponent model;
    bool hasModel = pScene->GetModel(entityID, model);
    if (!hasModel)
    {
        return;
    }

    if (model.isWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Set if the mesh should calculate lightning in shader
    GLint doNotLightUL = this->m_pShaderMediator->GetUL(shaderProgram, "doNotLight");
    glUniform1f(doNotLightUL, model.doNotLight);
}

void ModelSystem::Render(EntityID entityID, engine::Scene* pScene, std::string& shaderProgram)
{
    using namespace engine;

    ModelComponent model;
    bool hasModel = pScene->GetModel(entityID, model);
    if (!hasModel)
    {
        return;
    }

    sMesh* pMesh = this->m_pVAOManager->FindMeshByModelName(model.name);
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
