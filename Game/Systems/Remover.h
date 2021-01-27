#pragma once
#include "ECS.h"
#include "../Components/Components.h"

namespace Systems {
	class Remover : public ECS::System<Remover> {
	public:
		using Filter = ECS::Filters::Include<Components::ToRemoveTag>;

		ECS::Filters::Include<Components::ToRemoveTag> filter;
		REG_FILTERS(Remover, &filter);

		void run();
	};
}
