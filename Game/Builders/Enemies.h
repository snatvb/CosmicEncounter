#pragma once

#include "./default_includes.h"

namespace Builders {
	inline ECS::Entity& createEnemy(ECS::World& world, Engine::Game& game, Components::Transform::Position& position) {
		auto& entity = world.newEntity();
		auto tileSize = Size{ 32, 32 };
		entity.addComponent<Components::Transform>(position, tileSize);
		entity.addComponent<Components::CircleCollider>(16.0f, 16.0f, 16.0f);
		entity.addComponent<Components::EnemyTag>();
		auto texture = game.assets->textures.load("Assets/Ships/tile.png");

		auto gunOffset = Vector2D<float>{ 12, 32 };
		auto direction = Vector2D<float>{ 0, 1 };
		auto& gun = entity.addComponent<Components::Gun>(gunOffset, direction, 10.0f, 4.0f);
		gun.bulletSpeed = 800.0f;

		Vector2D<int> tileOffset{ 64, 64 };
		auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileOffset, tileSize);
		gfx.play = false;
		gfx.rotation = 180.0f;
		auto& stats = entity.addComponent<Components::HeroStats>();
		stats.speed = 450.0f;
		stats.health = 10.0f;
		return entity;
	}
}