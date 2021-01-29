#pragma once

#include "./DefaultIncludes.h"

namespace Systems {
	class Scenario : public ECS::System<Scenario> {
	public:
		ECS::Filters::Include<Components::Scenario> filter;
		REG_FILTERS(Scenario, &filter);

		void init() override;
		void run() override;
	};
}
