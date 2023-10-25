#include "EngineRenderer/Renderer.h"
#include "common/utils.h"

Renderer::Renderer()
{
	this->m_isRunning = false;
	this->m_isInitialized = false;
	
	this->m_currShaderID = -1;
	this->m_pShaderManager = nullptr;
	
	this->m_pWindowSystem = nullptr;
	this->m_pCameraSystem = nullptr;
	this->m_pModelSystem = nullptr;
	this->m_pLightSystem = nullptr;
}

Renderer::~Renderer()
{
	delete this->m_pShaderManager;

	delete this->m_pWindowSystem;
	delete this->m_pCameraSystem;
	delete this->m_pModelSystem;
	delete this->m_pLightSystem;
}

bool Renderer::Initialize(std::string baseShadersPath,
						  std::string baseModelsPath,
						  std::string shaderName,
						  uint windowWidth,
						  uint windowHeight,
						  const std::string& windowName,
						  GLFWkeyfun KeyCallback,
						  SceneView* pSceneView)
{
	if (this->m_isInitialized)
	{
		return true;
	}

	printf("Initializing engine renderer...\n");
	this->m_pShaderManager = new ShaderManager(baseShadersPath);
	// All systems that update info in shaders must have the shader info
	// To set their respectives uniforms and attributes
	this->m_pWindowSystem = new WindowSystem(this->m_pShaderManager);
	this->m_pCameraSystem = new CameraSystem(this->m_pShaderManager, pSceneView);
	this->m_pModelSystem = new ModelSystem(this->m_pShaderManager, pSceneView);
	this->m_pLightSystem = new LightSystem(this->m_pShaderManager, pSceneView);

	bool isWSInitialized = this->m_pWindowSystem->Initialize(windowWidth, 
															 windowHeight, 
															 windowName, 
															 KeyCallback);
	if (!isWSInitialized)
	{
		CheckEngineError("initializing Window system");
		return false;
	}

	printf("Creating shaders...\n");
	// Creates main shader program
	bool isShaderCreated = this->m_pShaderManager->AddShaderProgram(shaderName);
	if (!isShaderCreated)
	{
		CheckEngineError("creating shader program");
		return false;
	}
	this->m_currShaderID = this->m_pShaderManager->GetIDFromShaderProgramName(shaderName);
	this->m_pShaderManager->UseShaderProgram(this->m_currShaderID);

	// Setting up lights
	bool isLSInitialized = this->m_pLightSystem->Initialize(this->m_currShaderID);
	if (!isLSInitialized)
	{
		CheckEngineError("setting up lights");
		return false;
	}

	// Loading models into VAO and getting IDs
	this->LoadScene(baseModelsPath);

	this->m_isInitialized = true;
	this->m_isRunning = true;

    return true;
}

void Renderer::Destroy()
{
	if (!this->m_isInitialized)
	{
		return;
	}

	this->m_pWindowSystem->Destroy();

	this->m_isInitialized = false;

	return;
}

void Renderer::LoadScene(std::string baseModelsPath)
{
	this->m_pModelSystem->LoadModels(baseModelsPath, this->m_currShaderID);
	this->m_pLightSystem->Initialize(this->m_currShaderID);
}

void Renderer::NewFrame()
{
	if (!this->m_isInitialized)
	{
		return;
	}

	this->m_pShaderManager->UseShaderProgram(this->m_currShaderID);
	this->m_pWindowSystem->NewFrame(this->m_currShaderID);

	return;
}

void Renderer::DrawModel(EntityID entityID)
{
	if (!this->m_isInitialized)
	{
		return;
	}

	this->m_pWindowSystem->UpdateUL(this->m_currShaderID);
	this->m_pCameraSystem->UpdateUL(this->m_currShaderID);

	this->m_pModelSystem->UpdateUL(entityID, this->m_currShaderID);

	this->m_pModelSystem->Render(entityID);

	return;
}

void Renderer::EndFrame()
{
	if (!this->m_isInitialized)
	{
		return;
	}

	this->m_pWindowSystem->EndFrame();

	return;
}

bool Renderer::IsRunning()
{
	if (this->m_isRunning
		&& !this->m_pWindowSystem->WindowShouldClose())
	{
		return true;
	}
	else
	{
		return false;
	}
}
