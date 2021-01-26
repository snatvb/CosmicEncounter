#pragma once
#include "ECS.h"
#include "Engine.h"

namespace Systems {

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
