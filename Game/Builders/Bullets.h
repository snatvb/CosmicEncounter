#pragma once
#include "ECS.h"
#include "../Components/Components.h"
#include "../Assets.h"

namespace Builders {
	inline void createSimpleBullet(ECS::World& world, Components::Gun& gun, Components::Point& point) {
		Size tileSize{ 9, 15 };
		auto& game = Engine::Game::GetInstance();
		auto& entity = world.newEntity();
		entity.addComponent<Components::Transform>(point, tileSize);
		entity.addComponent<Components::Bullet>(gun.direction, gun.bulletSpeed, gun.damage);
		entity.addComponent<Components::CircleCollider>(4, 5, 3);

		auto texture = game.assets->textures.load(Assets::bullets);
		entity.addComponent<Components::GFXTexture>(*texture, tileSize);
	}
}
