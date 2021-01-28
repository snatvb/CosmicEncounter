#pragma once

#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"
#include "../Assets.h"

namespace Builders {
	inline void createStar(ECS::World& world, Vector2D<int>& offset, Components::Transform::Position& position, float speed = 0.0f) {
		auto texture = Engine::Game::GetInstance().assets->textures.load(Assets::starts);

		auto tileSize = Size{ 8, 8 };
		auto& entity = world.newEntity();
		auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, offset, tileSize);
		gfx.layer = static_cast<char>(Engine::Layer::Background);
		entity.addComponent<Components::Transform>(position);
		entity.addComponent<Components::Star>(speed);
	}
}

