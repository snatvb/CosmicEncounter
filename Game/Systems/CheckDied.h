#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class CheckDied : public ECS::System<CheckDied> {
	public:
		ECS::Filters::Include<Components::HeroStats> filter;
		REG_FILTERS(CheckDied, &filter);

		void run() override;
	};
}
