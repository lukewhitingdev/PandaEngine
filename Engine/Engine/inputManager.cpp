#include "inputManager.h"

#pragma region Functions for key presses

inputManager::inputManager()
{
	keyPressed = false;
}

inputManager* inputManager::getInstance()
{
	static inputManager* instance;
	if (!instance) {
		instance = new inputManager();
		return instance;
	}
}

// Allows the user to get one output for the duration the key is pressed.
bool inputManager::getKey(char key)
{
	if (getKeyDown(key)) {
		// If we are not holding a key already.
		if (keyPressed == false) {
			keyPressed = true;
			return true;
		}
		else {
			return false;
		}
	}
	if (getKeyUp(key)) {
		keyPressed = false;
		return false;
	}
}

bool inputManager::getKeyDown(char key)
{
	if (GetKeyState(key) & 0x8000) {
		return true;
	}
	else {
		return false;
	}
}

bool inputManager::getKeyUp(char key)
{
	if (GetKeyState(key) & 0x8000) {
		return false;
	}
	else {
		return true;
	}
}

#pragma endregion