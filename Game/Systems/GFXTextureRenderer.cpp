#include "GFXTextureRenderer.h"

namespace Systems {
	void GFXTextureRenderer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& position = entity->getComponent<Components::Position>();
			auto& scale = entity->getComponent<Components::Scale>();
			auto& gfx = entity->getComponent<Components::GFXTexture>();
			SDL_Rect rect;
			rect.x = position.x;
			rect.y = position.y;
			rect.w = scale.width;
			rect.h = scale.height;
			SDL_RenderCopy(_renderer, gfx.texture, NULL, &rect);
		}
	}
}
