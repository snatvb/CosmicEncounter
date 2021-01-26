#pragma once
#include "ECS.h"
#include "../Renderer.h"
#include "../Game.h"

namespace Systems {
	template<typename T>
	class RendererSystem : public ECS::System<T> {
	public:
		virtual void init() override;

	protected:
		Engine::Renderer* _renderer = nullptr;
	};
	
	template<typename T>
	inline void RendererSystem<T>::init()
	{
		_renderer = Engine::Game::GetRenderer();
	}
}
