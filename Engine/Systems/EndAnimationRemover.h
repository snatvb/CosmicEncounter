#pragma once

#include "ECS.h"
#include "../Components.h"

namespace Systems {
	class EndAnimationRemover : public ECS::System<EndAnimationRemover> {
	public:
		using Filter = ECS::Filters::With<
			Components::GFXAnimtion,
			Components::GFXDestroyByEndAnimationTag
		>;

		void run(ECS::FilteredEntities& entities) override;
	};
}
