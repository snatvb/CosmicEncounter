#pragma once

#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class ControlPlayer : public ECS::System<ControlPlayer> {
	public:
		using Filter = ECS::Filters::Include<Components::PlayerTag>;

		ECS::Filters::Include<Components::PlayerTag> playerFilter;

		REG_FILTERS(ControlPlayer, &playerFilter)

		void init() override;
		void run() override;
	private:
		Engine::Game* _game;
	};
}
