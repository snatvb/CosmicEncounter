#include "Texture.h"
#include "Debug.h"

namespace Assets {
	Textures::Textures(SDL_Renderer& renderer)
		: _renderer(&renderer)
	{
	}

	Textures::~Textures()
	{
		for (auto item : _textures) {
			clean(item.first);
		}
	}

	SDL_Texture* Textures::load(const char* path)
	{
		auto texture = _textures[path];
		if (texture) {
			return texture;
		}

		SDL_Surface* surface = IMG_Load(path);

		if (!surface) {
			Engine::Debug::Log("Error in loading texture", path);
			std::cout << (IMG_GetError()) << std::endl;
			return nullptr;
		}

		SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_FreeSurface(surface);

		_textures[path] = loadedTexture;

		return loadedTexture;
	}

	bool Textures::clean(const char* path)
	{
		auto texture = _textures[path];

		if (texture) {
			SDL_DestroyTexture(texture);
			_textures[path] = nullptr;
			return true;
		}

		return false;
	}
}

