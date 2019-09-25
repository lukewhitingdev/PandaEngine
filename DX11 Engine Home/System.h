#pragma once
#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "input.h"
#include "graphics.h"


class System
{
public:
	System();
	~System();

	bool Init();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MesageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:
	bool frame();
	void InitWindows(int& wWidth, int& wHeight);
	void ShutdownWindows();

	LPCWSTR m_ApplicationName;
	HINSTANCE m_HInstance;
	HWND mHWnd;

	input* m_Input;
	graphics* m_Graphics;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
};

// Global
static System* ApplicationHandle = 0;

