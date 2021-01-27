#pragma once

#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class Anchor : public ECS::System<Anchor> {
	public:
		ECS::Filters::With<Components::Anchor, Components::Transform> filter;
		REG_FILTERS(Anchor, &filter);

		void init() override {};
		void run() override;
	};
}
