#include "GFXAnimationRenderer.h"

inline SDL_Rect createDrawRect(Components::GFXAnimtion& gfx, Components::Transform& transform) {
	SDL_Rect drawRect;
	drawRect.x = static_cast<int>(transform.position.x);
	drawRect.y = static_cast<int>(transform.position.y);
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
			auto& transform = entity->getComponent<Components::Transform>();

			SDL_Rect clipRect = createClipRect(gfx);
			SDL_Rect drawRect = createDrawRect(gfx, transform);

			if (gfx.rotation > 0) {
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

			//SDL_Rect rect;
			//rect.x = static_cast<int>(transform.position.x);
			//rect.y = static_cast<int>(transform.position.y);
			//rect.w = 3;
			//rect.h = 3;
			//auto _renderer = Engine::Game::GetInstance().getRenderer();
			//SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			//SDL_RenderFillRect(_renderer, &rect);

			if (gfx.play) {
				moveFrame(gfx);
			}
		}
	}
}
