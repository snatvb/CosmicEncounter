#include "GFXShapeRenderer.h"

namespace Systems {
	void GFXRectRenderer::run()
	{
		for (auto& entity : *filter.entities) {
			auto& transform = entity->getComponent<Components::Transform>();
			auto& shapeGfx = entity->getComponent<Components::GFXShape>();
			auto& gfx = entity->getComponent<Components::GFXRect>();

			_renderer->add(shapeGfx.layer, [gfx, shapeGfx, transform](SDL_Renderer& sdlRenderer) {
				SDL_Rect rect;
				rect.x = static_cast<int>(transform.position.x);
				rect.y = static_cast<int>(transform.position.y);
				rect.w = static_cast<int>(gfx.size.width * transform.scale.width);
				rect.h = static_cast<int>(gfx.size.height * transform.scale.height);
				SDL_SetRenderDrawColor(&sdlRenderer, shapeGfx.color.r, shapeGfx.color.g, shapeGfx.color.b, 255);
				SDL_RenderFillRect(&sdlRenderer, &rect);
			});
		}
	}
}
