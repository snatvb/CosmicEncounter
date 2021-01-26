#pragma once
#include "RendererSystem.h"
#include "../Components/Components.h"

namespace Systems {
	class GFXTextureRenderer : public RendererSystem<Systems::GFXTextureRenderer> {
	public:
		using Filter = ECS::Filters::With<
			Components::GFXTexture,
			Components::Transform
		>;
		void run(ECS::FilteredEntities& entities) override;
	};
}
