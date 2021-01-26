#include "GFXRectRenderer.h"

namespace Systems {
	void GFXRectRenderer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& transform = entity->getComponent<Components::Transform>();
			auto& gfx = entity->getComponent<Components::GFXRect>();

			_renderer->add(gfx.layer, [gfx, transform](SDL_Renderer& sdlRenderer) {
				SDL_Rect rect;
				rect.x = static_cast<int>(transform.position.x);
				rect.y = static_cast<int>(transform.position.y);
				rect.w = static_cast<int>(transform.scale.width);
				rect.h = static_cast<int>(transform.scale.height);
				SDL_SetRenderDrawColor(&sdlRenderer, gfx.color.r, gfx.color.g, gfx.color.b, 255);
				SDL_RenderFillRect(&sdlRenderer, &rect);
			});
		}
	}
}
