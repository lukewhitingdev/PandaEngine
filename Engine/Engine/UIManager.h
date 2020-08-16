#pragma once
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_win32.h"
#include "../ImGUI/imgui_impl_dx11.h"
#include <vector>
#include <windows.h>
#include <d3d11_1.h>
#include "UI.h"

namespace PandaEngine {
	class UIManager
	{
	private:
		std::vector<UI*> UIElements;

	public:
		UIManager(HWND _hWnd, ID3D11Device* _device, ID3D11DeviceContext* _context);
		void addUI(UI* ui) { UIElements.push_back(ui); };
		void removeUI(UI ui);

		void Draw();
	};
}

