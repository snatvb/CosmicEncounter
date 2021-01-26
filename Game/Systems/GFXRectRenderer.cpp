#include "GFXRectRenderer.h"

namespace Systems {
	void GFXRectRenderer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& transform = entity->getComponent<Components::Transform>();
			auto& gfx = entity->getComponent<Components::GFXRect>();
			SDL_Rect rect;
			rect.x = (int)transform.position.x;
			rect.y = (int)transform.position.y;
			rect.w = (int)transform.scale.width;
			rect.h = (int)transform.scale.height;
			SDL_SetRenderDrawColor(_renderer, gfx.color.r, gfx.color.g, gfx.color.b, 255);
			SDL_RenderFillRect(_renderer, &rect);
		}
	}
}
