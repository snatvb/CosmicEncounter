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

	using RenderCache = std::array<std::vector<std::function<void(SDL_Renderer&)>>, static_cast<char>(Layer::Last)>;
}
