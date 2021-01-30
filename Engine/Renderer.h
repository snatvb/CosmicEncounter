#pragma once
#include <mutex>
#include "SDL.h"
#include "./Common.h"

namespace Engine {
	class Game;
	class Renderer {
	public:

		Renderer(SDL_Renderer& renderer) : _renderer(&renderer) {}

		inline void render() {
			mtx.lock();
			for (auto& layer : _functionsByLayers) {
				for (auto& [_, f] : layer) {
					f(*_renderer);
				}
				layer.clear();
			}
			_needRender = false;
			mtx.unlock();
		}

		inline void clear() {
			mtx.lock();
			for (auto& layer : _functionsByLayers) {
				layer.clear();
			}
			mtx.unlock();
		}

		inline void setNeedRender(bool needRender) {
			mtx.lock();
			_needRender = needRender;
			mtx.unlock();
		}

		inline bool getNeedRender() {
			return _needRender;
		}

		inline void add(char layer, ECS::EntityID id, const RenderCallback& callback) {
			mtx.lock();
			_functionsByLayers[layer][id] = callback;
			mtx.unlock();
		};

		inline void add(Layer layer, ECS::EntityID id, const RenderCallback& callback) {
			mtx.lock();
			_functionsByLayers[static_cast<int>(layer)][id] = callback;
			mtx.unlock();
		};
	private:
		std::mutex mtx;
		bool _needRender = false;
		RenderCache _functionsByLayers{};
		SDL_Renderer* _renderer = nullptr;
	};
}
