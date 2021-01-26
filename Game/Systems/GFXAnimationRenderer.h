#pragma once
#include "ECS.h"
#include "Common.h"
#include "../Components/Components.h"

namespace Systems {
	class GFXAnimationRenderer : public RendererSystem<Systems::GFXAnimationRenderer> {
	public:
		using Filter = ECS::Filters::With<Components::Transform, Components::GFXAnimtion>;

		GFXAnimationRenderer(Engine::RenderCache& cache) : RendererSystem(cache) {}

		void run(ECS::FilteredEntities& entities) override;
	};
}
