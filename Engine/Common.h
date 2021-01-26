#pragma once
#include <array>
#include <vector>
#include <functional>
#include "SDL.h"

namespace Engine {
	enum class Layer : char {
		Background,
		Default,
		Effects,
		Last
	};

	using RenderCallback = std::function<void(SDL_Renderer&)>;
	using RenderCache = std::array<std::vector<RenderCallback>, static_cast<char>(Layer::Last)>;
}
