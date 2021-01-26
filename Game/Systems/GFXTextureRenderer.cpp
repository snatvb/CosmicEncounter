#include "GFXTextureRenderer.h"

namespace Systems {
	void GFXTextureRenderer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& transform = entity->getComponent<Components::Transform>();
			auto& gfx = entity->getComponent<Components::GFXTexture>();

			SDL_Rect drawRect;
			drawRect.x = static_cast<int>(transform.position.x);
			drawRect.y = static_cast<int>(transform.position.y);
			drawRect.w = static_cast<int>(transform.scale.width);
			drawRect.h = static_cast<int>(transform.scale.height);

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

			if (gfx.rotation) {
				SDL_RenderCopyEx(
					_renderer,
					gfx.texture,
					&clipRect,
					&drawRect,
					gfx.rotation,
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
