#pragma once
#include "ECS.h"

namespace Systems {
	class Engine::Game;

	template<typename T>
	class RendererSystem : public ECS::System<T> {
	public:
		virtual void init() override;

	protected:
		SDL_Renderer* _renderer = nullptr;
	};
	
	template<typename T>
	inline void RendererSystem<T>::init()
	{
		_renderer = Engine::Game::GetInstance().getRenderer();
	}
}
