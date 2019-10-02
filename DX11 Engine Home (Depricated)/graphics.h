#pragma once

#include "direct3D.h"

// Globals

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 1000;
const float SCREEN_NEAR = 0.1f;

class graphics
{
public:
	graphics();
	~graphics();
	bool Init(int wWidth, int wHeight, HWND hwnd);
	void Shutdown();
	bool Frame();

private:
	direct3D* m_Direct3D;

	bool Render();
};
