#pragma once
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_win32.h"
#include "../ImGUI/imgui_impl_dx11.h"
#include <string>

namespace PandaEngine {
	class UI {
	public:
		virtual void render() {};
	};
}

