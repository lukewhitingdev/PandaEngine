#include "UIManager.h"


PandaEngine::UIManager::UIManager(HWND _hWnd, ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	UIElements = std::vector<UI*>();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui_ImplWin32_Init(_hWnd);
	ImGui_ImplDX11_Init(_device, _context);
	ImGui::StyleColorsDark();
}

void PandaEngine::UIManager::removeUI(UI ui)
{
	for (int i = 0; i < UIElements.size(); i++)
	{
		if (UIElements[i] == &ui) {
			UIElements.erase(UIElements.begin() + i);
		}
	}
}

void PandaEngine::UIManager::Draw()
{
	// Update GUI
	// Start the frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for each (UI* uiElement in UIElements)
	{
		uiElement->render();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
