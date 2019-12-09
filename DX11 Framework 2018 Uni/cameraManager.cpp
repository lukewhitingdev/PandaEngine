#include "cameraManager.h"



cameraManager::cameraManager()
{
}


cameraManager::~cameraManager()
{
}

Cam* cameraManager::getCurrentCamera()
{
	return currentCamera;
}

void cameraManager::setCurrentCamera(Cam* camera)
{
	currentCamera = camera;
}

Cam* cameraManager::getDefaultCamera()
{
	return currentCamera;
}

void cameraManager::setDefaultCamera(Cam* camera)
{
	defaultCamera = camera;
}
