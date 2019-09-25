#include "main.h"
#include "System.h"

/*

Will be edited beyond what is said in the tutorial but the base was created using the tutorial as a starting point

DirectX 11 Tutorial
Reference: http://www.rastertek.com/tutdx11.html

*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	System* sys;
	
	// Create the system class and fail startup if it cannot be initialized
	sys = new System;
	if (!sys) {
		return 0;
	}

	// If the system can be initalized run the app
	if (sys->Init()) {
		// Loop here
		sys->Run();
	}


	// Once run completes shutdown
	sys->Shutdown();
	delete sys;
	sys = 0;

	return 0;
}

