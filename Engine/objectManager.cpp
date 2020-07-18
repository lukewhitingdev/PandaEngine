#include "objectManager.h"

PandaEngine::objectManager::objectManager()
{
	_objectVector = std::vector<GameObject*>();
	_device = nullptr;
}