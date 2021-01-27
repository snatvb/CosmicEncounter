#pragma once

#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class EnemySpawner : public ECS::System<EnemySpawner> {
	public:
		using Filter = ECS::Filters::Include<Components::EnemyTag>;

		ECS::Filters::Include<Components::EnemyTag> filter;
		REG_FILTERS(EnemySpawner, &filter)

		void run() override;
	};
}
