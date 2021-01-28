#pragma once

#include "./DefaultIncludes.h"

namespace Systems {
	class StarsControl : public ECS::System<StarsControl> {
	public:
		ECS::Filters::With<
			Components::Transform,
			Components::GFXAnimtion,
			Components::Star
		> filter;
		REG_FILTERS(StarsControl, &filter);

		void init() override;
		void run() override;
	};
}
