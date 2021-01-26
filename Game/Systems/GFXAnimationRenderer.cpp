#include "GFXAnimationRenderer.h"

inline SDL_Rect createDrawRect(Components::GFXAnimtion& gfx, Components::Position& position) {
	SDL_Rect drawRect;
	drawRect.x = position.x;
	drawRect.y = position.y;
	drawRect.w = gfx.tileSize.width;
	drawRect.h = gfx.tileSize.height;
	return drawRect;
}

inline SDL_Rect createClipRect(Components::GFXAnimtion& gfx) {
	SDL_Rect clipRect;
	clipRect.x = gfx.offset.x + gfx.tileSize.width * gfx.currentFrame.x - gfx.tileSize.width;
	clipRect.y = gfx.offset.y + gfx.tileSize.height * gfx.currentFrame.y - gfx.tileSize.height;
	clipRect.w = gfx.tileSize.width;
	clipRect.h = gfx.tileSize.height;
	return clipRect;
}

inline void moveFrame(Components::GFXAnimtion& gfx) {
	if (gfx.frameCooldown <= 0) {
		gfx.currentFrame.x = gfx.currentFrame.x % gfx.frames.x;
		if (gfx.currentFrame.x == 0) {
			gfx.currentFrame.y = (gfx.currentFrame.y % gfx.frames.y) + 1;
		}
		gfx.currentFrame.x += 1;

		gfx.frameCooldown = ((double)Components::GFXAnimtion::FPS / 1000) / gfx.speed;
	}
	else {
		gfx.frameCooldown -= Engine::Game::GetInstance().time.delta();
	}
}

namespace Systems {
	void GFXAnimationRenderer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& gfx = entity->getComponent<Components::GFXAnimtion>();
			auto& position = entity->getComponent<Components::Position>();

			SDL_Rect clipRect = createClipRect(gfx);
			SDL_Rect drawRect = createDrawRect(gfx, position);

			SDL_RenderCopy(_renderer, gfx.texture, &clipRect, &drawRect);

			if (gfx.play) {
				moveFrame(gfx);
			}
		}
	}
}
