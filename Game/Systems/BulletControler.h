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

		ECS::Filters::With<
			Components::Transform,
			Components::Bullet
		> filter;
		REG_FILTERS(BulletControl, &filter)

		void init() override;
		void run() override;
	private:
		Engine::Game* _game;
	};
}
