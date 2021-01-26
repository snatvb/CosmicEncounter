#include "GFXTextureRenderer.h"

namespace Systems {
	void GFXTextureRenderer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& position = entity->getComponent<Components::Position>();
			auto& size = entity->getComponent<Components::Size>();
			auto& gfx = entity->getComponent<Components::GFXTexture>();
			SDL_Rect rect;
			rect.x = position.x;
			rect.y = position.y;
			rect.w = size.width;
			rect.h = size.height;
			SDL_RenderCopy(_renderer, gfx.texture, NULL, &rect);
		}
	}
}
