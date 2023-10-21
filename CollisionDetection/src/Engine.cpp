#include "Engine.h"
#include "ConfigReadWriteFactory.h"

Engine::Engine()
{
	this->m_isInitialized = false;
	this->m_shaderProgramName = "";

	this->m_pShaderManager = nullptr;

	this->m_pModelSystem = nullptr;
	this->m_pTransformSystem = nullptr;
	this->m_pWindowSystem = nullptr;
	this->m_pCameraSystem = nullptr;

	this->m_pScene = nullptr;
}

Engine::~Engine()
{
	delete this->m_pShaderManager;
	delete this->m_pModelSystem;
	delete this->m_pTransformSystem;
	delete this->m_pWindowSystem;
	delete this->m_pCameraSystem;
	delete this->m_pScene;
}

bool Engine::Initialize(const std::string& sceneName)
{
	if (this->m_isInitialized)
	{
		// Already initialized
		return true;
	}

	printf("Initializing creation of scene '%s'\n", sceneName.c_str());

	this->m_pScene = new myecs::sScene();
	iConfigReadWrite* pConfigrw = ConfigReadWriteFactory::CreateConfigReadWrite("json");

	// Load all database files
	// TODO: All this should come from a config file
	std::string baseConfigsPath = "configs/";
	std::string sceneFilePath = baseConfigsPath + sceneName + ".json";
	std::string baseShadersPath = "assets/shaders/";
	std::string baseModelPath = "assets/models/";
	this->m_shaderProgramName = "Shader01";
	uint windowWidth = 1080;
	uint windowHeight = 720;
	std::string windowName = sceneName;

	printf("Loading configs...\n");
	// Load scene components and entities from database file
	bool isSceneLoaded = pConfigrw->ReadScene(sceneFilePath, this->m_pScene);
	if (!isSceneLoaded)
	{
		printf("Error loading scene data!\n");
		return false;
	}

	delete pConfigrw;

	printf("Creating systems...\n");
	this->m_pShaderManager = new ShaderManager(baseShadersPath);
	this->m_pModelSystem = new ModelSystem(this->m_pShaderManager);
	this->m_pWindowSystem = new WindowSystem(this->m_pShaderManager);
	this->m_pCameraSystem = new CameraSystem(this->m_pShaderManager);
	this->m_pTransformSystem = new TransformSystem(this->m_pShaderManager);

	printf("Initializing rendering api...\n");
	bool isWindowSystemInitialized = this->m_pWindowSystem->Initialize(windowWidth, windowHeight, windowName);
	if (!isWindowSystemInitialized)
	{
		printf("Error initializing Window system!\n"); // TODO: Remove error handling repetition
		return false;
	}

	printf("Creating shaders...\n");
	// Creates main shader program
	bool isShaderCreated = this->m_pShaderManager->AddShaderProgram(this->m_shaderProgramName);
	if (!isShaderCreated)
	{
		printf("Error creating shader program!\n"); // TODO: Remove error handling repetition
		return false;
	}

	printf("Initializing systems...\n");
	// Initializes all systems
	bool isModelSystemInitialized = this->m_pModelSystem->Initialize(baseModelPath, this->m_pScene);
	if (!isModelSystemInitialized)
	{
		printf("Error initializing Model system!\n"); // TODO: Remove error handling repetition
		return false;
	}

	bool isCameraSystemInitialized = this->m_pCameraSystem->Initialize();
	if (!isCameraSystemInitialized)
	{
		printf("Error initializing Camera system!\n"); // TODO: Remove error handling repetition
		return false;
	}

	bool isTransformSystemInitialized = this->m_pTransformSystem->Initialize();
	if (!isTransformSystemInitialized)
	{
		printf("Error initializing Transform system!\n"); // TODO: Remove error handling repetition
		return false;
	}

	this->m_isInitialized = true;
	printf("Scene '%s' created scussesfully!\n", sceneName.c_str());

    return true;
}

void Engine::Destroy()
{
	this->m_pModelSystem->Destroy();
	this->m_pWindowSystem->Destroy();
	this->m_pCameraSystem->Destroy();
	this->m_pTransformSystem->Destroy();
	return;
}

void Engine::Update()
{
}
