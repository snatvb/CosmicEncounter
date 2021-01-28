#pragma once

#include "./DefaultIncludes.h"

namespace Systems {
	class ControlPlayer : public ECS::System<ControlPlayer> {
	public:
		ECS::Filters::Include<Components::PlayerTag> playerFilter;

		REG_FILTERS(ControlPlayer, &playerFilter)

		void init() override;
		void run() override;
	private:
		Engine::Game* _game;
	};
}
