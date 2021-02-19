#pragma once
#include "./DefaultIncludes.h"

namespace Systems {
	class TechBossAI : public ECS::System<TechBossAI> {
	public:
		ECS::Filters::Include<Components::TechBoss> filter;
		ECS::Filters::Include<Components::PlayerTag> playerFilter;
		REG_FILTERS(TechBossAI, &filter, &playerFilter);

		void init() override;
		void run() override;
	};
}
