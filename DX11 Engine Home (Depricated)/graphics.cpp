#include "graphics.h"



graphics::graphics()
{
	m_Direct3D = 0;
}


graphics::~graphics()
{
}

bool graphics::Init(int wWidth, int wHeight, HWND hwnd)
{
	// Create the Direct3D object
	m_Direct3D = new direct3D;

	if (!m_Direct3D) {
		return false;
	}

	// Initalise Direct3D
	if (!m_Direct3D->Init(wWidth, wHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR)) {
		MessageBox(hwnd, L"Could not initialize Direct3D!", L"Error: ", MB_OK);
		return false;
	}


	// If all goes well continue
	return true;

}

void graphics::Shutdown()
{
	if (m_Direct3D) {
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	return;
}

bool graphics::Frame()
{

	// Render the scene
	if (!Render()) {
		return false;
	}

	return true;
}

bool graphics::Render()
{
	// Clear the buffers
	m_Direct3D->BeginScene(0.0f, 1.0f, 1.0f, 1.0f);

	// Present the scene to screen / flip buffers
	m_Direct3D->EndScene();

	return true;
}
