#pragma once

#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class EnemySpawner : public ECS::System<EnemySpawner> {
	public:
		using Filter = ECS::Filters::Include<Components::EnemyTag>;

		void run(ECS::FilteredEntities& entities) override;
	};
}
