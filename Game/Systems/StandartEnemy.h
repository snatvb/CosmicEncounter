#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class StandartEnemy : public ECS::System<StandartEnemy> {
	public:
		ECS::Filters::With<
			Components::Transform,
			Components::EnemyTag,
			Components::HeroStats
		> filter;
		ECS::Filters::Include<Components::PlayerTag> playerFilter;
		REG_FILTERS(StandartEnemy, &filter, &playerFilter)

		void init() override;
		void run() override;
	private:
		Engine::Game* _game = nullptr;
	};
}
