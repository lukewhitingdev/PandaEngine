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
	parentedCameraVector.push_back(new CameraParentContainer(camera, parentMesh, offset));
}

void cameraManager::updateParentedCameras()
{
	
	for (int i = 0; i < parentedCameraVector.size(); i++) {
		// If the camera and mesh are out of line
		if (Util::compareXMFLOAT3(parentedCameraVector[i]->_cam->getCameraPos(), parentedCameraVector[i]->_mesh->getPosition())) {
			parentedCameraVector[i]->_cam->setCameraPos(parentedCameraVector[i]->_mesh->getPosition().x,
															parentedCameraVector[i]->_mesh->getPosition().y,
															parentedCameraVector[i]->_mesh->getPosition().z);
		}
	}
	
}
