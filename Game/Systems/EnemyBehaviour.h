#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class EnemyBehaviour : public ECS::System<EnemyBehaviour> {
	public:
		ECS::Filters::With<
			Components::Transform,
			Components::Enemy,
			Components::HeroStats
		> filter;
		ECS::Filters::Include<Components::PlayerTag> playerFilter;
		REG_FILTERS(EnemyBehaviour, &filter, &playerFilter)

		void init() override;
		void run() override;
	private:
		Engine::Game* _game = nullptr;
	};
}
