#include "GFXTextureRenderer.h"

namespace Systems {
	void GFXTextureRenderer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& position = entity->getComponent<Components::Position>();
			auto& gfx = entity->getComponent<Components::GFXTexture>();

			SDL_Rect drawRect;
			drawRect.x = position.x;
			drawRect.y = position.y;

			if (entity->hasComponent<Components::Scale>()) {
				auto& scale = entity->getComponent<Components::Scale>();
				drawRect.w = scale.width;
				drawRect.h = scale.height;
			}

			SDL_Rect clipRect;
			clipRect.x = gfx.offset.x;
			clipRect.y = gfx.offset.y;

			if (gfx.tileSize.has_value()) {
				auto& size = gfx.tileSize.value();
				clipRect.w = size.width;
				clipRect.h = size.height;
			}
			else {
				SDL_QueryTexture(gfx.texture, NULL, NULL, &clipRect.w, &clipRect.h);
			}

			SDL_RenderCopy(_renderer, gfx.texture, &clipRect, &drawRect);
		}
	}
}
