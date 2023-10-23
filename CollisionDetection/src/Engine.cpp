#include "Engine.h"
#include "scene/Scene.h"
#include "ConfigReadWriteFactory.h"
#include "events/KeyWrapper.h"
#include "common/utils.h"

// TODO: Map all data used by the other classes from the scene
// to pass only the needed data and decouple all from scene

Engine::Engine()
{
	this->m_pRenderer = nullptr;
	this->m_pEditor = nullptr;

	this->m_isInitialized = false;
	this->m_isRunning = false;

	this->m_pKeyEvent = nullptr;

	this->m_pScene = nullptr;
	this->m_pSceneView = nullptr;
}

Engine::~Engine()
{
	delete this->m_pRenderer;
	delete this->m_pEditor;
	delete this->m_pScene;
	delete this->m_pSceneView;
}

bool Engine::Initialize(const std::string& sceneName)
{
	if (this->m_isInitialized)
	{
		// Already initialized
		return true;
	}

	printf("Initializing creation of scene '%s'\n", sceneName.c_str());

	this->m_pScene = new Scene();
	this->m_pSceneView = new SceneView(this->m_pScene);
	iConfigReadWrite* pConfigrw = ConfigReadWriteFactory::CreateConfigReadWrite("json");

	// Load all database files
	// TODO: All this should come from a config file
	std::string baseConfigsPath = "configs/";
	std::string sceneFilePath = baseConfigsPath + sceneName + ".json";
	std::string baseShadersPath = "assets/shaders/";
	std::string baseModelPath = "assets/models/";
	std::string shaderProgramName = "Shader01";
	uint windowWidth = 1080;
	uint windowHeight = 720;
	std::string windowName = sceneName;

	printf("Loading configs...\n");
	// Load scene components and entities from database file
	bool isSceneLoaded = pConfigrw->ReadScene(sceneFilePath, this->m_pScene);
	if (!isSceneLoaded)
	{
		CheckEngineError("Scene loading");
		return false;
	}

	delete pConfigrw; // Used only to load all configs

	// Events
	this->m_pKeyEvent = new KeyEvent();
	KeyWrapper::SetKeyEvent(this->m_pKeyEvent);

	printf("Creating systems...\n");
	this->m_pRenderer = new Renderer();
	this->m_pEditor = new Editor(this->m_pKeyEvent, this->m_pSceneView);

	printf("Initializing systems...\n");
	// Initializes all systems
	bool isERInitialized = this->m_pRenderer->Initialize(baseShadersPath,
														 baseModelPath,
														 shaderProgramName,
														 windowWidth,
														 windowHeight,
														 windowName,
														 KeyWrapper::KeyCallback,
														 this->m_pSceneView);
	if (!isERInitialized)
	{
		CheckEngineError("Engine renderer initializing");
		return false;
	}

	this->m_isInitialized = true;
	this->m_isRunning = true;
	printf("Scene '%s' created scussesfully!\n", sceneName.c_str());

    return true;
}

void Engine::Destroy()
{
	if (!this->m_isInitialized)
	{
		return;
	}

	this->m_pRenderer->Destroy();
	this->m_isInitialized = false;

	return;
}

void Engine::Update()
{
	if (!this->m_isInitialized)
	{
		return;
	}

	this->m_pRenderer->NewFrame();

	for (EntityID entityID = 0; entityID < this->m_pScene->GetNumEntities(); entityID++)
	{
		this->m_pRenderer->DrawModel(entityID);
	}

	this->m_pRenderer->EndFrame();
}

bool Engine::IsRunning()
{
	if (this->m_isRunning
		&& this->m_pRenderer->IsRunning()
		&& this->m_pEditor->IsRunning())
	{
		return true;
	}
	else
	{
		return false;
	}
}
