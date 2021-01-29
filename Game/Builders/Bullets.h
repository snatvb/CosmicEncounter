#pragma once
#include "./default_includes.h"

namespace Builders {
	using CollideLayers = std::vector<CollideLayer>;
	void createSimpleBullet(
		ECS::World& world,
		Engine::Game& game,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	);

	void createSimpleBullet(
		ECS::World& world,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	);
}
