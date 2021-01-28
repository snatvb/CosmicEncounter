#pragma once
#include "../game_common.h"

namespace Builders {
	inline void createSimpleExplosion(ECS::World& world, Components::Transform& transform) {
		auto texture = Engine::Game::GetInstance().assets->textures.load(AssetPathes::simpleExplostion);

		auto tileSize = Size{ 32, 32 };
		auto& entity = world.newEntity();
		Vector2D<int> frames{ 5, 1 };
		auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileSize, frames);
		gfx.layer = static_cast<char>(Engine::Layer::Effects);
		gfx.speed = 0.5f;
		entity.addComponent<Components::Transform>(transform.position);
		entity.addComponent<Components::GFXDestroyByEndAnimationTag>();
	}
}
