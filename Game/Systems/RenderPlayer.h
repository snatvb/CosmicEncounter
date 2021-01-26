#pragma once
#include "Engine.h"
#include "ECS.h"
#include "../Components/Components.h"

namespace Systems {
	class RenderPlayer : public ECS::System<Systems::RenderPlayer> {
	public:
		using Filter = ECS::Filters::Include<Components::PlayerTag>;


		void init() override;
		void run(ECS::FilteredEntities& entities) override;

	private:
		SDL_Renderer* _renderer = nullptr;
	};
}
