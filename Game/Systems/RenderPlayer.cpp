#include "RenderPlayer.h"

namespace Systems {
	void RenderPlayer::init() {
		_renderer = Engine::Game::GetInstance().getRenderer();
	}

	void RenderPlayer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
		}
	}
}
