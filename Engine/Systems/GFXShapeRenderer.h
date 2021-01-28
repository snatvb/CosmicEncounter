#pragma once
#include "ECS.h"
#include "./RendererSystem.h"
#include "../Components.h"

namespace Systems {
	class GFXShapeRenderer : public RendererSystem<Systems::GFXShapeRenderer> {
	public:
		ECS::Filters::With<
			Components::GFXRect,
			Components::Transform
		> rects;

		ECS::Filters::With<
			Components::GFXRect,
			Components::Transform
		> circles;

		REG_FILTERS(GFXShapeRenderer, &rects, &circles)

		void run() override;
	};
}
