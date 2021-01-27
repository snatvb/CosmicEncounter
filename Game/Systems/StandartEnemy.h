#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class StandartEnemy : public ECS::System<StandartEnemy> {
	public:
		using Filter = ECS::Filters::With<Components::Transform, Components::EnemyTag, Components::HeroStats>;

		ECS::Filters::With<
			Components::Transform,
			Components::EnemyTag,
			Components::HeroStats
		> filter;
		REG_FILTERS(StandartEnemy, &filter)

		void init() override;
		void run() override;
	private:
		Engine::Game* _game = nullptr;
		ECS::Filter* _playerFilter = nullptr;
	};
}
