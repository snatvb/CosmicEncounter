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
		if (auto texture = _textures[path]) {
			return texture;
		}

		SDL_Surface* surface = IMG_Load(path);

		if (!surface) {
			const auto error = IMG_GetError();
			Engine::Debug::Error("Error in loading texture", path);
			Engine::Debug::Error(error);
			return nullptr;
		}

		Engine::Debug::Error("Loaded new texture", path);
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
			Engine::Debug::Log("Clear memory texture", path);
			return true;
		}

		return false;
	}
}

