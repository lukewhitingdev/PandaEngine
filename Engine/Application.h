#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <vector>
#include "resource.h"
#include "Engine/DDSTextureLoader.h"
#include "Engine/Structures.h"
#include "Engine/OBJLoader.h"
#include "Engine/objectIncludes.h"
#include "Engine/LightingIncludes.h"
#include "Engine/cameraIncludes.h"
#include "Engine/GameTimer.h"
#include "Engine/cameraManager.h"
#include "Engine/saveToFileManager.h"
#include "Engine/lightingManager.h"
#include "Engine/Engine.h"
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

