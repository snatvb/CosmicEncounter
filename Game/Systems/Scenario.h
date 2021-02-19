#pragma once

#include "./DefaultIncludes.h"

namespace Systems {
	class Scenario : public ECS::System<Scenario> {
	public:
		ECS::Filters::Include<Components::Scenario> filter;
		ECS::Filters::With<
			Components::Enemy,
			Components::Collided,
			Components::ToRemoveTag
		> enemiesCollided;
		REG_FILTERS(Scenario, &filter, &enemiesCollided);

		void init() override;
		void run() override;
		void _handleKills(const ECS::Entity& enemyEntity, Components::Scenario& scenario);
	};
}
