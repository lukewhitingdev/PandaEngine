#include "System.h"



System::System()
{
	m_Input = 0;
	m_Graphics = 0;
}

System::~System()
{
}

/// Handles setup of the windows API, Graphics and input classes
bool System::Init()
{
	int windowWidth = 0;
	int windowHeight = 0;

	// Start the windows api
	InitWindows(windowWidth, windowHeight);

	// Init input object to capture inputs from the user
	m_Input = new input;
	if (!m_Input){
		return false;
	}
	m_Input->Init();

	// Init graphics object to handle rendering
	m_Graphics = new graphics;
	if (!m_Graphics) {
		return false;
	}
	if (!m_Graphics->Init(windowWidth, windowHeight, mHWnd)) {
		return false;
	}
	
	// Everything is ok
	return true;
}

/// Handles cleanup of Windows API, Graphics and Input objects
void System::Shutdown()
{
	if (m_Graphics) {
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	if (m_Input) {
		delete m_Input;
		m_Input = 0;
	}

	// Note: not actually windows, just the window used for the app lol
	ShutdownWindows();

	return;
}

void System::Run()
{
	MSG msg;

	bool done = false;

	// Init msg struct
	ZeroMemory(&msg, sizeof(MSG));

	while (!done) {
		// Windows messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// if windows signals to end the app
		if (msg.message == WM_QUIT) {
			done = true;
		}
		else {
			// If the rendering in the frame function completes then do just loop, if something goes wrong stop running.
			if (!frame()) {
				done = true;
			}
		}
	}
}

LRESULT System::MesageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg) {
		// if a key has been pressed
		case WM_KEYDOWN:
			// Send it to the input to record it
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
			
		// if a key has been lifted
		case WM_KEYUP:
			// Send it to the input to record it
			m_Input->KeyUp((unsigned int)wparam);
			return 0;

		default:
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
}

bool System::frame()
{
	// check if Esc is pressed and wants to exit the app
	if (m_Input->IsKeyDown(VK_ESCAPE)) {
		return false;
	}

	// if the frame processing on the graphics end doesnt fail then continue
	if (!m_Graphics->Frame()) {
		return false;
	}
	// If all the processing goes well and the user doesnt wanna quit continue
	return true;
}

/// Used to create the window to be rendered into
void System::InitWindows(int & wWidth, int & wHeight)
{
	WNDCLASSEX WndClass;
	DEVMODE dmScreenSettings;
	int posX = 0;
	int posY = 0;

	// Get external pointer to this object
	ApplicationHandle = this;

	// Get instance of application
	m_HInstance = GetModuleHandle(NULL);

	// Top name on window
	m_ApplicationName = L"Pebo Engine";

	// Setup windows class with default setuo
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = m_HInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	WndClass.hIconSm = WndClass.hIcon;
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = m_ApplicationName;
	WndClass.cbSize = sizeof(WNDCLASSEX);

	// Register the class
	RegisterClassEx(&WndClass);


	// Get the resolution of the current clients screen
	wWidth = GetSystemMetrics(SM_CXSCREEN);
	wHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup screen setting if the fullscreen is true or not
	if (FULL_SCREEN) {
		// If full screen set the screen to maximum size of the users desktop
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)wWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)wHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else {
		// Windowed
		// set to 800x600 resolution.
		wWidth = 800;
		wHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - wWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - wHeight) / 2;
	}
	// Create the window and get a handle from it
	mHWnd = CreateWindowEx(WS_EX_APPWINDOW,
						m_ApplicationName,
						m_ApplicationName,
						WS_TILEDWINDOW,
						posX,
						posY,
						wWidth,
						wHeight,
						NULL,
						NULL,
						m_HInstance,
						NULL);

	// Maximise the window and make it be the focus
	ShowWindow(mHWnd, SW_SHOW);
	SetForegroundWindow(mHWnd);
	SetFocus(mHWnd);

	ShowCursor(false);

	return;
}

/// Cleans up the window handles and resets all the values back to 0 or null
void System::ShutdownWindows()
{
	ShowCursor(true);

	// Fix display settings when leaving full screen mode
	if (FULL_SCREEN) {
		ChangeDisplaySettings(NULL, 0);
	}

	// Destroy the window and application instance
	DestroyWindow(mHWnd);
	mHWnd = NULL;
	UnregisterClass(m_ApplicationName, m_HInstance);
	m_HInstance = NULL;

	// Reset pointer to the class
	ApplicationHandle = NULL;

	return;

}

LRESULT System::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg) {
		// if the window is being destroyed
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		// if the window is being destroyed
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		default:
			return ApplicationHandle->MesageHandler(hwnd, umsg, wparam, lparam);
	}
}
