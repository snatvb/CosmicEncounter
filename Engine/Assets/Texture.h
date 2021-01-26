#pragma once
#include <vector>
#include <map>
#include "SDL.h"
#include "SDL_image.h"

namespace Assets {
	class Textures {
	public:

		Textures(SDL_Renderer& renderer);
		~Textures();

		SDL_Texture* load(const char* path);
		bool clean(const char* path);

	private:
		SDL_Renderer* _renderer;
		std::map<const char*, SDL_Texture*> _textures;
	};
}
