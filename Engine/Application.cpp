#include "Application.h"
#include "DDSTextureLoader.h"

Application::Application()
{
	Engine = new PandaEngine::Engine();
	fileManager = nullptr;
	objMeshLoader = MeshData();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
	return Engine->Init(hInstance, nCmdShow);
}

void Application::InitCamera()
{

	Engine->addCameraManager();

	PandaEngine::cameraManager* camManager = Engine->getCameraManager();

	// Initialize the view matrix
	XMFLOAT3 Eye = XMFLOAT3(0.0f, 0.0f, -3.0f);
	XMFLOAT3 At = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 To = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3 Right = XMFLOAT3(1.0f, 0.0f, 0.0f);

	camManager->addCamera(new debugCamera(Eye, To, Up, Right, (float)Engine->Window->getWindowWidth(), (float)Engine->Window->getWindowHeight(), 0.0f, 1000.0f));
	camManager->getCameraAtIndex(0)->UpdateStoredFloats();

	Eye = XMFLOAT3(0.0f, 2.0f, -3.0f);

	camManager->addCamera(new staticCamera(Eye, At, (float)Engine->Window->getWindowWidth(), (float)Engine->Window->getWindowHeight(), 0.0f, 1000.0f));
	camManager->getCameraAtIndex(1)->UpdateStoredFloats();

	Eye = XMFLOAT3(0.0f, 20.0f, 1.0f);

	camManager->addCamera(new staticGeneratedCamera(Eye, To, (float)Engine->Window->getWindowWidth(), (float)Engine->Window->getWindowHeight(), 0.0f, 1000.0f));
	camManager->getCameraAtIndex(2)->UpdateStoredFloats();


	Eye = XMFLOAT3(0.0f, 0.0f, 0.0f);
	To = XMFLOAT3(0.0f, 0.0f, -1.0f);

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

	objManager->createCubeGameObject(new Transform(), L"Assets/Textures/Crate/Crate_COLOR.dds");
	GameObject* cubeMesh2 = objManager->getObjectAtIndex(objManager->objectCount() - 1);

	objManager->createSphereGameObject(new Transform(), L"Assets/Textures/Crate/Crate_COLOR.dds");
	GameObject* sphereMesh = objManager->getObjectAtIndex(objManager->objectCount() - 1);

	objManager->createCustomGameObject(new Transform(), L"Assets/Textures/Plane/Hercules_COLOR.dds", "Assets/Object Models/Custom/Boat.obj", true);
	GameObject* shipMesh = objManager->getObjectAtIndex(objManager->objectCount() - 1);

	objManager->createCustomGameObject(new Transform(), L"Assets/Textures/Debug/defaultTex.dds", "Assets/Object Models/Custom/Box.obj", true);
	GameObject* enclosureMesh = objManager->getObjectAtIndex(objManager->objectCount() - 1);

	objManager->createCustomGameObject(new Transform(), L"Assets/Textures/Debug/defaultTex.dds", "Assets/Object Models/Custom/Wall.obj", true);
	GameObject* floorCube = objManager->getObjectAtIndex(objManager->objectCount() - 1);

	objManager->createCubeGameObject(new Transform(), L"Assets/Textures/Crate/Crate_COLOR.dds");
	GameObject* physCube = objManager->getObjectAtIndex(objManager->objectCount() - 1);

	objManager->createCubeGameObject(new Transform(), L"Assets/Textures/Crate/Crate_COLOR.dds");
	GameObject* physCube2 = objManager->getObjectAtIndex(objManager->objectCount() - 1);

	objManager->createCubeGameObject(new Transform(), L"Assets/Textures/Crate/Crate_COLOR.dds");
	GameObject* physCube3 = objManager->getObjectAtIndex(objManager->objectCount() - 1);


	// Generate Ocean
	for (int i = 0; i < 3; i++) {
		objManager->createCustomGameObject(new Transform(), L"Assets/Textures/Water/Ocean.dds", "Assets/Object Models/Custom/Plane.obj", Mesh::meshType::WAVE);
	}

	if (fileManager->getLoadObjectsFromFile()) {

		// Get the loaded positions from the file.
		vector<XMFLOAT3> loadedPositions = fileManager->LoadPositionsFromFile();

		// Load all the positions currently saved, make sure that if some objects arent saved properly, then it will not overrun the vector.
		for (size_t i = 0; i < loadedPositions.size(); i++) {
			if (i < objManager->objectCount()) {
				objManager->getObjectAtIndex(i)->getTransformComponent()->setPosition(loadedPositions[i]);
				objManager->getObjectAtIndex(i)->getTransformComponent()->setScale(0.3f);
			}
		}

		// Loop through the rest of the mesh vector to reset all the new objects positions to 0 so they can be aligned within the program.
		if (objManager->objectCount() > loadedPositions.size()) {
			for (size_t i = loadedPositions.size(); i < objManager->objectCount(); i++) {
				objManager->getObjectAtIndex(i)->getTransformComponent()->setPosition(XMFLOAT3(0, 0, 0));
			}
		}

		// Hardset scale vars
		for (size_t i = 0; i < objManager->objectCount(); i++) {
			// Set the scale of the water
			if (objManager->getObjectAtIndex(i)->getMeshComponent()->getMeshType() == Mesh::meshType::WAVE) {
				objManager->getObjectAtIndex(i)->getTransformComponent()->setScale(XMFLOAT3(1.8f, 2.5f, 3.0f));
				objManager->getObjectAtIndex(i)->getTransformComponent()->setPosition(XMFLOAT3(1.5f, -0.2f, 1.8f));
			}
		}

		enclosureMesh->getTransformComponent()->setPosition(XMFLOAT3(10.0f, -20.0f, 0.0f));
		enclosureMesh->getTransformComponent()->setScale(XMFLOAT3(1.25f, 1.25f, 1.25f));

		shipMesh->getTransformComponent()->setPosition(XMFLOAT3(0.0f, 2.0f, 12.0f));
		shipMesh->getTransformComponent()->setRotation(XMFLOAT3(0.0f, XMConvertToRadians(45.0f), 0.0f));
		shipMesh->getTransformComponent()->setScale(0.6f);

		floorCube->getTransformComponent()->setPosition(XMFLOAT3(-3.5f, 0.0f, -5.0f));
		floorCube->getTransformComponent()->setScale(XMFLOAT3(1.0f, 0.7f, 0.5f));
		floorCube->getTransformComponent()->setRotation(XMFLOAT3(0.0f, 0.0f, XMConvertToRadians(90.0f)));

		// Player Cube

		physCube->addRigidBody();
		physCube->addInputManager();
		physCube->addPlayerController();
		physCube->getRigidbodyComponent()->setMass(1.0f);
		physCube->getRigidbodyComponent()->setCollisionSphere(new sphereCollider(physCube->getTransformComponent()->getVector3Position(), 1.0f));
		physCube->getTransformComponent()->setPosition(XMFLOAT3(-7.0f, 1.25f, -10.0f));
		physCube->getTransformComponent()->setScale(1.0f);

		// Debug Phys Cube

		physCube2->addRigidBody();
		physCube2->getRigidbodyComponent()->setCollisionSphere(new sphereCollider(physCube2->getTransformComponent()->getVector3Position(), 1.0f));
		physCube2->makeGameObjectStatic(true);
		physCube2->getTransformComponent()->setPosition(XMFLOAT3(3.0f, 1.25f, -10.0f));
		physCube2->getTransformComponent()->setScale(1.0f);

		// Spinning Phys Cube

		physCube3->addRigidBody();
		physCube3->addRotator(1.0f);
		physCube3->addInputManager();
		physCube3->getRigidbodyComponent()->setCollisionSphere(new sphereCollider(physCube3->getTransformComponent()->getVector3Position(), 1.0f));
		physCube3->makeGameObjectStatic(true);
		physCube3->getTransformComponent()->setPosition(XMFLOAT3(0.0f, 3.0f, 0.0f));
		physCube3->getTransformComponent()->setScale(1.0f);

		fileManager->SavePositionsToFile(objManager->getObjectVector());
	}
	else {
		// Use this to position objects and save them to the file for later.
		cubeMesh->getTransformComponent()->setPosition(XMFLOAT3(-4.0f, 0.0f, 0.1f));
		cubeMesh->getTransformComponent()->setScale(0.3f);

		cubeMesh2->getTransformComponent()->setPosition(XMFLOAT3(4.0f, 0.0f, 0.1f));
		cubeMesh2->getTransformComponent()->setScale(0.3f);

		sphereMesh->getTransformComponent()->setPosition(XMFLOAT3(0.0f, 2.0f, 30.0f));
		sphereMesh->getTransformComponent()->setScale(0.3f);

		shipMesh->getTransformComponent()->setPosition(XMFLOAT3(0.0f, 0.2f, 20.0f));
		shipMesh->getTransformComponent()->setScale(0.3f);

		fileManager->SavePositionsToFile(objManager->getObjectVector());
	}
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