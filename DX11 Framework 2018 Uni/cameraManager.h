#pragma once
#include "Cam.h"
#include "objectIncludes.h"
#include <vector>

class cameraManager
{
public:
	cameraManager();
	~cameraManager();

	Cam* getCurrentCamera();
	void setCurrentCamera(Cam* camera);

	Cam* getDefaultCamera();
	void setDefaultCamera(Cam* camera);

	void PairCameraToMesh(Mesh* parentMesh, Cam* camera, XMFLOAT3 offset);

	void updateParentedCameras();

private:

	Cam* currentCamera;
	Cam* defaultCamera;

	std::vector<Cam*> cameraVector;
	//std::vector<CameraParentContainer*> parentedCameraVector;
};

