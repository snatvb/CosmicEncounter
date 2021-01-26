#include "RenderPlayer.h"

namespace Systems {
	void RenderPlayer::init() {
		_renderer = Engine::Game::GetInstance().getRenderer();
	}

	void RenderPlayer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& position = entity->getComponent<Components::Position>();
			auto& size = entity->getComponent<Components::Scale>();
			auto& gfx = entity->getComponent<Components::GFX>();
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
