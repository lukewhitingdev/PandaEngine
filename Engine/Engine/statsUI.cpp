#include "statsUI.h"

statsUI::statsUI()
{
}

void statsUI::render()
{
	ImGui::Begin("Stats");
	ImGui::Text("Frame Stats %.4f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}
