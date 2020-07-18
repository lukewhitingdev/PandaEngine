#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <vector>
#include "resource.h"
#include "Structures.h"
using namespace DirectX;

namespace PandaEngine {
	class window
	{
	private:
		// DX11 and Windows API
		HINSTANCE               _hInst;
		HWND                    _hWnd;

		UINT _WindowHeight;
		UINT _WindowWidth;

		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

	public:
		HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

		// Getters
		HWND gethWnd()						{ return _hWnd; };
		UINT getWindowHeight()				{ return _WindowHeight; };
		UINT getWindowWidth()				{ return _WindowWidth; };
 	};
}

