#include "Application.h"
#include "Timer.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Application * theApp = new Application();
	Timer* frameTimer = new Timer();

	if (FAILED(theApp->Initialise(hInstance, nCmdShow)))
	{
		return -1;
	}

    // Main message loop
    MSG msg = {0};

	// Reset the timer to initalize the prev frame var
	frameTimer->Reset();

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
			frameTimer->Tick();
			theApp->CalculateFrameStats(frameTimer->GameTime());
			theApp->Update(frameTimer->DeltaTime());
            theApp->Draw();
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}