#pragma once
#include "Cam.h"
#include "objectIncludes.h"
#include "UtlilityClass.h"
#include <vector>

namespace PandaEngine {
	class cameraManager
	{
	public:
		cameraManager();
		~cameraManager();

		Cam* getCurrentCamera();
		void setCurrentCamera(Cam* camera);

		Cam* getDefaultCamera();
		void setDefaultCamera(Cam* camera);

		void addCamera(Cam* camera);
		Cam* getCameraAtIndex(int index);

		std::vector<Cam*> getCameraVector() { return cameraVector; };

	private:

		Cam* currentCamera;
		Cam* defaultCamera;

		std::vector<Cam*> cameraVector;
	};
}

