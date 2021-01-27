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

		ECS::Filters::With<
			Components::GFXAnimtion,
			Components::GFXDestroyByEndAnimationTag
		> filter;

		REG_FILTERS(EndAnimationRemover, &filter)

		void run() override;
	};
}
