#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class StandartEnemy : public ECS::System<StandartEnemy> {
	public:
		using Filter = ECS::Filters::With<Components::Transform, Components::EnemyTag, Components::HeroStats>;

		void init() override;
		void run(ECS::FilteredEntities& entities) override;
	private:
		Engine::Game* _game;
	};
}
