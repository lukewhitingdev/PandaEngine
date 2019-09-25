#pragma once

#include <Windows.h>

// Globals

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000;
const float SCREEN_NEAR = 0.1f;

class graphics
{
public:
	graphics();
	~graphics();
	bool Init(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();
};
