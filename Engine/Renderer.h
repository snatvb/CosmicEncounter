#pragma once
#include "SDL.h"
#include "./Common.h"

namespace Engine {
	class Game;
	class Renderer {
	public:

		Renderer(SDL_Renderer& renderer) : _renderer(&renderer) {}

		inline void render() {
			for (auto& layer : _functionsByLayers) {
				for (auto& f : layer) {
					f(*_renderer);
				}
				layer.clear();
			}
		}

		inline void add(char layer, const RenderCallback& callback) {
			_functionsByLayers[layer].emplace_back(callback);
		};

		inline void add(Layer layer, const RenderCallback& callback) {
			_functionsByLayers[static_cast<int>(layer)].emplace_back(callback);
		};
	private:
		RenderCache _functionsByLayers{};
		SDL_Renderer* _renderer = nullptr;
	};
}
