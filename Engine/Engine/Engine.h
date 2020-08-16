#pragma once
#include "window.h"
#include "renderer.h"

 namespace PandaEngine {
	class Engine
	{
	public:
		Engine();
		~Engine();
		HRESULT Init(HINSTANCE hInstance, int nCmdShow);
		void update();
		void draw();

		void addCameraManager() { CameraManager = new cameraManager(); Renderer->addCameraManager(CameraManager); };
		cameraManager* getCameraManager() { return CameraManager; };
		void addLightingManager() { LightingManager = new lightingManager(); Renderer->addLightingManager(LightingManager); };
		lightingManager* getLightingManager() { return LightingManager; };
		void addObjectManager() { ObjectManager = new objectManager(); Renderer->addObjectManager(ObjectManager); };
		objectManager* getObjectManager() { return ObjectManager; };
		void addGameTimer() { gameTimer = new GameTimer(); Renderer->addGameTimer(gameTimer); };
		GameTimer* getGameTimer() { return gameTimer; };
		void addUIManager() { uiManager = new UIManager(Window->gethWnd(), Renderer->getDevice(), Renderer->getDeviceContext()); Renderer->addUIManager(uiManager); }
		UIManager* getUIManager() { return uiManager; }

	public:
		// Internals
		window*		Window;
		renderer*	Renderer;

	protected:
		// Managers
		cameraManager*		CameraManager;
		lightingManager*	LightingManager;
		objectManager*		ObjectManager;
		GameTimer*			gameTimer;
		UIManager*			uiManager;

	private:
		void initGameTimer();
		void initUIManager();
		void initDefaultDebugUI();
	};
}


