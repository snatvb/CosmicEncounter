#pragma once
#include "ECS.h"
#include "../Components/Components.h"

namespace Systems {
	class Remover : public ECS::System<Remover> {
	public:
		using Filter = ECS::Filters::Include<Components::ToRemoveTag>;

		void run(ECS::FilteredEntities& entities);
	};
}
