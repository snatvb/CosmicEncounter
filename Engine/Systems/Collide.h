#pragma once
#include "ECS.h"
#include "../Components.h"

namespace Systems {
	class Collide : public ECS::System<Collide> {
	public:
		ECS::Filters::Include<Components::CircleCollider> filter;

		REG_FILTERS(Collide, &filter)

		void run() override;
	};
}
