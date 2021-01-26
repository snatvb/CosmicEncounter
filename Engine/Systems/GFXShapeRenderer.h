#pragma once
#include "ECS.h"
#include "./RendererSystem.h"
#include "../Components.h"

namespace Systems {
	class GFXRectRenderer : public RendererSystem<Systems::GFXRectRenderer> {
	public:
		using Filter = ECS::Filters::With<
			Components::GFXRect,
			Components::Transform
		>;
		void run(ECS::FilteredEntities& entities) override;
	};
}
