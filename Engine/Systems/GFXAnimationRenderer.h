#pragma once
#include "ECS.h"
#include "Common.h"
#include "RendererSystem.h"
#include "../Components.h"

namespace Systems {
	class GFXAnimationRenderer : public RendererSystem<Systems::GFXAnimationRenderer> {
	public:
		using Filter = ECS::Filters::With<Components::Transform, Components::GFXAnimtion>;

		void run(ECS::FilteredEntities& entities) override;
	};
}
