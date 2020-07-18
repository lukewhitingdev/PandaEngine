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
	initGameTimer(Window->gethWnd());
	result = Renderer->Initialise();
	return result;
}

void PandaEngine::Engine::initGameTimer(HWND _hWnd)
{
	addGameTimer();
	gameTimer->ResetTimer();
	gameTimer->CalculateFrameStats(_hWnd);
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
		CameraManager->getCurrentCamera()->updateCameraMovement(CameraManager->getCameraVector());
}

void PandaEngine::Engine::draw()
{
	if(Renderer)
		Renderer->Draw();
}
