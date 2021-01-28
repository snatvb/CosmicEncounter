#pragma once
#include "./default_includes.h"

namespace Builders {
	using CollideLayers = std::vector<CollideLayer>;
	inline void createSimpleBullet(
		ECS::World& world,
		Engine::Game& game,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	) {
		Size tileSize{ 9, 15 };
		auto& entity = world.newEntity();
		entity.addComponent<Components::Transform>(point, tileSize);
		entity.addComponent<Components::Bullet>(gun.direction, gun.bulletSpeed, gun.damage);

		auto& collider = entity.addComponent<Components::CircleCollider>(4.0f, 5.0f, 3.0f);
		collider.layer = static_cast<size_t>(CollideLayer::Bullet);
		for (auto layer : ignoreLayers) {
			collider.layers[static_cast<size_t>(layer)] = false;
		}

		auto texture = game.assets->textures.load(AssetPathes::bullets);
		auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileSize);
		gfx.play = false;
		gfx.rotation = gun.direction.y > 0 ? 180.0f : 0.0f;
	}

	inline void createSimpleBullet(
		ECS::World& world,
		Components::Gun& gun,
		Components::Point& point,
		CollideLayers& ignoreLayers
	) {
		auto& game = Engine::Game::GetInstance();
		createSimpleBullet(world, game, gun, point, ignoreLayers);
	}
}
