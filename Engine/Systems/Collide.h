#pragma once
#include "ECS.h"
#include "../Components.h"

namespace Systems {
	class Collide : public ECS::System<Collide> {
	public:
		using Filter = ECS::Filters::Include<Components::CircleCollider>;

		void run(ECS::FilteredEntities& entities) override;
	};
}
