#pragma once
#include "ECS.h"

namespace Systems {
	class Engine::Game;

	template<typename T>
	class RendererSystem : public ECS::System<T> {
	public:
		virtual void init() override;
		RendererSystem(Engine::RenderCache& cache) : _renderCache(cache) {}

	protected:
		Engine::RenderCache& _renderCache;
		SDL_Renderer* _renderer = nullptr;
	};
	
	template<typename T>
	inline void RendererSystem<T>::init()
	{
		_renderer = Engine::Game::GetInstance().getRenderer();
	}
}
