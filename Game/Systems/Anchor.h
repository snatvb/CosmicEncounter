#pragma once

#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class Anchor : public ECS::System<Anchor> {
	public:
		using Filter = ECS::Filters::With<Components::Anchor, Components::Position>;

		void init() override {};
		void run(ECS::FilteredEntities& enitites) override;
	};
}
