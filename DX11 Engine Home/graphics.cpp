#include "graphics.h"



graphics::graphics()
{
}


graphics::~graphics()
{
}

bool graphics::Init(int, int, HWND)
{
	return true;
}

void graphics::Shutdown()
{
}

bool graphics::Frame()
{
	return true;
}

bool graphics::Render()
{
	return false;
}
