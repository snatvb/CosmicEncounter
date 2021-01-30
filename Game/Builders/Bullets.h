#pragma once
#include "./default_includes.h"

namespace Builders {
	using CollideLayers = std::vector<CollideLayer>;

	ECS::Entity& createDefaultBullet(
		ECS::World& world,
		Engine::Game& game,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	);

	ECS::Entity& createGrenadeBullet(
		ECS::World& world,
		Engine::Game& game,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	);

	ECS::Entity* createBulletByGun(
		ECS::World& world,
		Engine::Game& game,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	);

	ECS::Entity* createBulletByGun(
		ECS::World& world,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	);
}
