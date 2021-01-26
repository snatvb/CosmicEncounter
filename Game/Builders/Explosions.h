#pragma once
#include "ECS.h"
#include "Game.h"
#include "../Components/Components.h"
#include "../Assets.h"

namespace Builders {
	inline void createSimpleExplosion(ECS::World& world, Components::Transform& transform) {
		auto texture = Engine::Game::GetInstance().assets->textures.load(Assets::simpleExplostion);

		auto tileSize = Size{ 32, 32 };
		auto& entity = world.newEntity();
		Vector2D<int> frames{ 5, 1 };
		entity.addComponent<Components::GFXAnimtion>(*texture, tileSize, frames);
		entity.addComponent<Components::Transform>(transform.position);
	}
}
