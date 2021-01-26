#pragma once
#include <array>
#include <vector>
#include <functional>

namespace Engine {
	enum class Layer : char {
		Background,
		Default,
		Effects,
		Last
	};

	using RenderCache = std::array<std::vector<std::function<void()>>, static_cast<char>(Layer::Last)>;
}
