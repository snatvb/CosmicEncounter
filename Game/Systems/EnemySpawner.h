#pragma once

#include "./DefaultIncludes.h"

namespace Systems {
	class EnemySpawner : public ECS::System<EnemySpawner> {
	public:
		ECS::Filters::Include<Components::EnemyTag> filter;
		REG_FILTERS(EnemySpawner, &filter)

		void run() override;
	};
}
