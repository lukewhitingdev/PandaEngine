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

void cameraManager::PairCameraToMesh(Mesh* parentMesh, Cam* camera, XMFLOAT3 offset)
{
	XMFLOAT3 meshPos = parentMesh->getPosition();
	camera->setCameraPos(meshPos.x + offset.x, meshPos.y + offset.y, meshPos.z + offset.z);
	//parentedCameraVector.push_back(new CameraParentContainer(camera, parentMesh, offset));
}

void cameraManager::updateParentedCameras()
{
	/*
	for (int i = 0; i < parentedCameraVector.size(); i++) {
		// If the camera and mesh are out of line
		if (!Util::compareXMFLOAT3(parentedCameraVector[i]->camera->getCameraPos(), parentedCameraVector[i]->mesh->getPosition())) {
			parentedCameraVector[i]->camera->setCameraPos(parentedCameraVector[i]->mesh->getPosition().x,
															parentedCameraVector[i]->mesh->getPosition().y,
															parentedCameraVector[i]->mesh->getPosition().z);
		}
	}
	*/
}
