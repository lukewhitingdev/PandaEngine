#pragma once
#include "Cam.h"
#include "objectIncludes.h"
#include "UtlilityClass.h"
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

private:

	Cam* currentCamera;
	Cam* defaultCamera;

	std::vector<Cam*> cameraVector;
};

