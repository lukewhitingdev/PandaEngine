#pragma once
#include <Windows.h>

// Singleton class to handle key inputs.

class inputManager
{
public:

	inputManager();
	static inputManager* getInstance();

	bool getKey(char key);
	bool getKeyDown(char key);
	bool getKeyUp(char key);

private:
	bool keyPressed;
};

