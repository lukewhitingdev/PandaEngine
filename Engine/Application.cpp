#include "Application.h"
#include "Engine/DDSTextureLoader.h"

Application::Application()
{
	Engine = new PandaEngine::Engine();
	fileManager = nullptr;
	objMeshLoader = MeshData();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
	HRESULT result = Engine->Init(hInstance, nCmdShow);
	if (result == S_OK) {
		InitCamera();
		InitObjects();
		InitLighting();
	}
	return result;
}

void Application::InitCamera()
{

	Engine->addCameraManager();

	PandaEngine::cameraManager* camManager = Engine->getCameraManager();

	// Initialize the view matrix
	XMFLOAT3 Eye = XMFLOAT3(0.0f, 2.0f, -3.0f);
	XMFLOAT3 At = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 To = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3 Right = XMFLOAT3(1.0f, 0.0f, 0.0f);

	camManager->addCamera(new staticCamera(Eye, To, (float)Engine->Window->getWindowWidth(), (float)Engine->Window->getWindowHeight(), 0.0f, 1000.0f));
	camManager->getCameraAtIndex(0)->UpdateStoredFloats();

	//camManager->addCamera(new debugCamera(Eye, To, Up, Right, (float)Engine->Window->getWindowWidth(), (float)Engine->Window->getWindowHeight(), 0.0f, 1000.0f));
	//camManager->getCameraAtIndex(0)->UpdateStoredFloats();

	camManager->setDefaultCamera(camManager->getCameraAtIndex(0));
	camManager->setCurrentCamera(camManager->getCameraAtIndex(0));
}

void Application::InitObjects()
{
	Engine->addObjectManager();
	PandaEngine::objectManager* objManager = Engine->getObjectManager();

	fileManager = new saveToFileManager("Assets/ObjectPositions/MeshPos.txt");

	// Whether you would like to load from a file or not.
	fileManager->setLoadObjectsFromFile(true);

	objManager->createCubeGameObject(new Transform(), L"Assets/Textures/Crate/Crate_COLOR.dds");
	objManager->getObjectAtIndex(objManager->objectCount() - 1);
	GameObject* cubeMesh = objManager->getObjectAtIndex(objManager->objectCount() - 1);


	// Generate Ocean
	for (int i = 0; i < 3; i++) {
		objManager->createCustomGameObject(new Transform(), L"Assets/Textures/Water/Ocean.dds", "Assets/Object Models/Custom/Plane.obj", Mesh::meshType::WAVE);
	}

	// Use this to position objects and save them to the file for later.
	cubeMesh->getTransformComponent()->setPosition(XMFLOAT3(0.0f, 1.0f, 0.1f));
	cubeMesh->getTransformComponent()->setScale(1.0f);

	fileManager->SavePositionsToFile(objManager->getObjectVector());

}

void Application::InitLighting()
{
	Engine->addLightingManager();
	PandaEngine::lightingManager* lightManager = Engine->getLightingManager();
	
	lightManager->addDirectionalLight(Engine->getCameraManager());
}

void Application::Update()
{
	Engine->update();
}

void Application::Draw()
{
	Engine->draw();
}