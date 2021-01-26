#include "GFXTextureRenderer.h"

namespace Systems {
	void GFXTextureRenderer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& transform = entity->getComponent<Components::Transform>();
			auto& gfx = entity->getComponent<Components::GFXTexture>();

			SDL_Rect drawRect;
			drawRect.x = (int)transform.position.x;
			drawRect.y = (int)transform.position.y;
			drawRect.w = (int)transform.scale.width;
			drawRect.h = (int)transform.scale.height;

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

			if (transform.rotation > 0) {
				SDL_RenderCopyEx(
					_renderer,
					gfx.texture,
					&clipRect,
					&drawRect,
					transform.rotation,
					NULL,
					SDL_FLIP_NONE
				);
			}
			else {
				SDL_RenderCopy(_renderer, gfx.texture, &clipRect, &drawRect);
			}

		}
	}
}
