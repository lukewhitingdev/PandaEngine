#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <vector>
#include "resource.h"
#include "DDSTextureLoader.h"
#include "Structures.h"
#include "OBJLoader.h"
#include "objectIncludes.h"
#include "LightingIncludes.h"
#include "cameraIncludes.h"
#include "GameTimer.h"
#include "cameraManager.h"
#include "saveToFileManager.h"
#include "lightingManager.h"
#include "Engine.h"
using namespace DirectX;



class Application
{

private:

	// Loader
	MeshData objMeshLoader;

	saveToFileManager* fileManager;

	PandaEngine::Engine* Engine;

private:
	void InitCamera();
	void InitObjects();
	void InitLighting();

public:
	Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	void Update();
	void Draw();
};

