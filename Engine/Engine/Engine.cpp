#include "Engine.h"

PandaEngine::Engine::Engine() {
	Window = new PandaEngine::window();
	Renderer = new PandaEngine::renderer(Window);
	CameraManager = nullptr;
	gameTimer = nullptr;
	LightingManager = nullptr;
	ObjectManager = nullptr;
}

PandaEngine::Engine::~Engine()
{
	CameraManager = nullptr;
	gameTimer = nullptr;
	LightingManager = nullptr;
	ObjectManager = nullptr;
}

HRESULT PandaEngine::Engine::Init(HINSTANCE hInstance, int nCmdShow)
{
	HRESULT result;
	result = Window->Initialise(hInstance, nCmdShow);
	initGameTimer();
	result = Renderer->Initialise();
	initUIManager();
	initDefaultDebugUI();
	return result;
}

void PandaEngine::Engine::initGameTimer()
{
	addGameTimer();
	gameTimer->ResetTimer();
}

void PandaEngine::Engine::initUIManager()
{
	addUIManager();
}

void PandaEngine::Engine::initDefaultDebugUI()
{
	uiManager->addUI(new DockingUI());
	uiManager->addUI(new InspectorUI());
}

void PandaEngine::Engine::update()
{
	if (ObjectManager) {
		for (size_t i = 0; i < ObjectManager->objectCount(); i++) {
			if (gameTimer)
				ObjectManager->getObjectAtIndex(i)->Update(gameTimer->getDeltaTime());

			for (size_t j = 0; j < ObjectManager->objectCount(); j++)
			{
				if (ObjectManager->getObjectAtIndex(i) != ObjectManager->getObjectAtIndex(j))														// Make sure we dont get collisions on ourself duh.
					ObjectManager->getObjectAtIndex(i)->updateCollisions(ObjectManager->getObjectAtIndex(i), ObjectManager->getObjectAtIndex(j));	// Check collisions with the current gameObject will all other gameObject in scene.
			}
		}
	}

	if(CameraManager)
		CameraManager->getCurrentCamera()->updateCameraMovement();

	if (gameTimer) {
		gameTimer->Tick();
		HWND hwnd = Window->gethWnd();
		gameTimer->CalculateFrameStats(hwnd);
	}
}

void PandaEngine::Engine::draw()
{
	if(Renderer)
		Renderer->Draw();
}
