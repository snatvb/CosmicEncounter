#pragma once
#include "ECS.h"
#include "../Components/Components.h"
#include "RendererSystem.h"

namespace Systems {
	class GFXAnimationRenderer : public RendererSystem<Systems::GFXAnimationRenderer> {
	public:
		using Filter = ECS::Filters::With<Components::Position, Components::GFXAnimtion>;

		void run(ECS::FilteredEntities& entities) override;
	};
}
