#pragma once
#include "ECS.h"
#include "./RendererSystem.h"
#include "../Components.h"

namespace Systems {
	class GFXRectRenderer : public RendererSystem<Systems::GFXRectRenderer> {
	public:
		ECS::Filters::With<
			Components::GFXRect,
			Components::Transform
		> filter;

		REG_FILTERS(GFXRectRenderer, &filter)

		void run() override;
	};
}
