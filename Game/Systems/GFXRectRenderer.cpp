#include "GFXRectRenderer.h"

namespace Systems {
	void GFXRectRenderer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& position = entity->getComponent<Components::Position>();
			auto& size = entity->getComponent<Components::Size>();
			auto& gfx = entity->getComponent<Components::GFXRect>();
			SDL_Rect rect;
			rect.x = position.x;
			rect.y = position.y;
			rect.w = size.width;
			rect.h = size.height;
			SDL_SetRenderDrawColor(_renderer, gfx.color.r, gfx.color.g, gfx.color.b, 255);
			SDL_RenderFillRect(_renderer, &rect);
		}
	}
}
