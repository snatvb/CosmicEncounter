#pragma once

#include "Assets/Texture.h"

namespace Assets {
	class Manager {
	public:
		Textures textures;

		Manager(SDL_Renderer& renderer) : textures(Textures(renderer)) {};
	};
}
