#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class BulletControl : public ECS::System<BulletControl> {
	public:
		using Filter = ECS::Filters::With<
			Components::Transform,
			Components::Bullet
		>;

		void init() override;
		void run(ECS::FilteredEntities& entities) override;
	private:
		Engine::Game* _game;
	};
}
