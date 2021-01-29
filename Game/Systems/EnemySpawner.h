#pragma once

#include "./DefaultIncludes.h"

namespace Systems {
	class EnemySpawner : public ECS::System<EnemySpawner> {
	public:
		ECS::Filters::Include<Components::Enemy> filter;
		ECS::Filters::Include<Components::Scenario> scenarios;
		REG_FILTERS(EnemySpawner, &filter, &scenarios);

		void run() override;
		void spawnStandart();
	};
}
