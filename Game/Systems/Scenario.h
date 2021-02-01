#pragma once

#include "./DefaultIncludes.h"

namespace Systems {
	class Scenario : public ECS::System<Scenario> {
	public:
		ECS::Filters::Include<Components::Scenario> filter;
		ECS::Filters::With<
			Components::Enemy,
			Components::Collided
		> enemiesCollided;
		REG_FILTERS(Scenario, &filter);

		void init() override;
		void run() override;
	};
}
