#include "cameraManager.h"



PandaEngine::cameraManager::cameraManager()
{
	cameraVector = std::vector<Cam*>();
	currentCamera = nullptr;
	defaultCamera = nullptr;
}


PandaEngine::cameraManager::~cameraManager()
{
}

Cam* PandaEngine::cameraManager::getCurrentCamera()
{
	return currentCamera;
}

void PandaEngine::cameraManager::setCurrentCamera(Cam* camera)
{
	currentCamera = camera;
}

Cam* PandaEngine::cameraManager::getDefaultCamera()
{
	return currentCamera;
}

void PandaEngine::cameraManager::setDefaultCamera(Cam* camera)
{
	defaultCamera = camera;
}

void PandaEngine::cameraManager::addCamera(Cam* camera)
{
	cameraVector.push_back(camera);
}

Cam* PandaEngine::cameraManager::getCameraAtIndex(int index)
{
	return cameraVector[index];
}
