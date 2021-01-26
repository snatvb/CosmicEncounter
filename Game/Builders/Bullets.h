#pragma once
#include "ECS.h"
#include "../Components/Components.h"
#include "../Assets.h"

namespace Builders {
	inline void createSimpleBullet(ECS::World& world, Engine::Game& game, Components::Gun& gun, Components::Point& point) {
		Size tileSize{ 9, 15 };
		auto& entity = world.newEntity();
		entity.addComponent<Components::Transform>(point, tileSize);
		entity.addComponent<Components::Bullet>(gun.direction, gun.bulletSpeed, gun.damage);
		entity.addComponent<Components::CircleCollider>(4.0f, 5.0f, 3.0f);

		auto texture = game.assets->textures.load(Assets::bullets);
		auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileSize);
		gfx.play = false;
		gfx.rotation = gun.direction.y > 0 ? 180.0f : 0.0f;
	}

	inline void createSimpleBullet(ECS::World& world, Components::Gun& gun, Components::Point& point) {
		auto& game = Engine::Game::GetInstance();
		createSimpleBullet(world, game, gun, point);
	}
}
