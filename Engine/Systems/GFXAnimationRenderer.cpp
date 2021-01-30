#include "GFXAnimationRenderer.h"
#include "../Game.h"

inline SDL_Rect createDrawRect(const Components::GFXAnimtion& gfx, const Components::Transform& transform) {
	SDL_Rect drawRect;
	drawRect.x = static_cast<int>(transform.position.x);
	drawRect.y = static_cast<int>(transform.position.y);
	drawRect.w = gfx.tileSize.width;
	drawRect.h = gfx.tileSize.height;
	return drawRect;
}

inline SDL_Rect createClipRect(const Components::GFXAnimtion& gfx) {
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
	void GFXAnimationRenderer::run()
	{
		for (auto& entity : *filter.entities) {
			auto& gfx = entity->getComponent<Components::GFXAnimtion>();
			auto& transform = entity->getComponent<Components::Transform>();
			_renderer->add(gfx.layer, entity->id, [gfx, transform](SDL_Renderer& sdlRenderer) {
				SDL_Rect clipRect = createClipRect(gfx);
				SDL_Rect drawRect = createDrawRect(gfx, transform);
				if (gfx.rotation > 0) {
					SDL_RenderCopyEx(
						&sdlRenderer,
						gfx.texture,
						&clipRect,
						&drawRect,
						gfx.rotation,
						NULL,
						SDL_FLIP_NONE
					);
				}
				else {
					SDL_RenderCopy(&sdlRenderer, gfx.texture, &clipRect, &drawRect);
				}
			});

			if (gfx.play) {
				moveFrame(gfx);
			}
		}
	}
}
