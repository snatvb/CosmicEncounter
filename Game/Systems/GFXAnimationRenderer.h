#pragma once
#include "ECS.h"
#include "../Components/Components.h"

namespace Systems {
	class GFXAnimationRenderer : public RendererSystem<Systems::GFXAnimationRenderer> {
	public:
		using Filter = ECS::Filters::With<Components::Transform, Components::GFXAnimtion>;

		void run(ECS::FilteredEntities& entities) override;
	};
}
