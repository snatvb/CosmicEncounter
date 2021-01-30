#pragma once
#include <array>
#include <map>
#include <functional>
#include "SDL.h"
#include "ECS.h"

namespace Engine {
	enum class Layer : char {
		Background,
		Default,
		Effects,
		Last
	};

	using RenderCallback = std::function<void(SDL_Renderer&)>;
	using RenderCache = std::array<std::map<ECS::EntityID, RenderCallback>, static_cast<char>(Layer::Last)>;
}
