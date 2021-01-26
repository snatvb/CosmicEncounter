#pragma once

#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class Input : public ECS::System<Input> {
	public:
		using Filter = ECS::Filters::Include<Components::PlayerTag>;

		void init() override;
		void run(ECS::FilteredEntities& enitites) override;
	private:
		Engine::Game* _game;

		void _handleMove(ECS::Entity& entity);
	};
}
