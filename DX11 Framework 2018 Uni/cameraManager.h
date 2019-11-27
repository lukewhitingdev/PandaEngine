#pragma once
#include "Cam.h"
#include "objectIncludes.h"
#include "UtlilityClass.h"
#include <vector>

class cameraManager
{

	struct CameraParentContainer {
		Cam* _cam = nullptr;
		Mesh* _mesh = nullptr;
		XMFLOAT3 _offset = XMFLOAT3(0.0f, 0.0f, 0.0f);

		CameraParentContainer(Cam* camera, Mesh* mesh,  XMFLOAT3 offset) {
			_cam = camera;
			_mesh = mesh;
			_offset = offset;
		}
	};

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
	std::vector<CameraParentContainer*> parentedCameraVector;
};

