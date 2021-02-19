#pragma once
#include "./default_includes.h"

namespace Builders {
	using CollideLayers = std::vector<CollideLayer>;

	ECS::Entity& createDefaultBullet(
		ECS::World& world,
		ECS::EntityID ownerId,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	);

	ECS::Entity& createGrenadeBullet(
		ECS::World& world,
		ECS::EntityID ownerId,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	);

	ECS::Entity& createFoilBullet(
		ECS::World& world,
		ECS::EntityID ownerId,
		const Components::Gun& gun,
		const Components::Point& point,
		const CollideLayers& ignoreLayers
	);

	ECS::Entity* createBulletByGun(
		ECS::World& world,
		ECS::EntityID ownerId,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	);
}
