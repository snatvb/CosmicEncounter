#include "Enemies.h"

ECS::Entity& Builders::createStandartEnemy(ECS::World& world, Engine::Game& game, Components::Transform::Position& position) {
	auto& entity = world.newEntity();

	auto tileSize = Size{ 32, 32 };
	entity.addComponent<Components::Transform>(position, tileSize);
	auto& collider = entity.addComponent<Components::CircleCollider>(16.0f, 16.0f, 16.0f);
	collider.layer = static_cast<size_t>(CollideLayer::Enemy);

	entity.addComponent<Components::EnemyTag>();
	auto texture = game.assets->textures.load(AssetPathes::shipsTile);

	auto gunOffset = Vector2D<float>{ 12, 32 };
	auto direction = Vector2D<float>{ 0, 1 };
	auto& gun = entity.addComponent<Components::Gun>(gunOffset, direction, 10.0f, 4.0f);
	gun.bulletSpeed = 700.0f;

	Vector2D<int> tileOffset{ 64, 64 };
	auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileOffset, tileSize);
	gfx.play = false;
	gfx.rotation = 180.0f;
	auto& stats = entity.addComponent<Components::HeroStats>();
	stats.speed = 450.0f;
	stats.health = 10.0f;
	return entity;
}

ECS::Entity& Builders::createBombardirEnemy(ECS::World& world, Engine::Game& game, Components::Transform::Position& position)
{
	auto& entity = world.newEntity();

	auto tileSize = Size{ 32, 32 };
	entity.addComponent<Components::Transform>(position, tileSize);
	auto& collider = entity.addComponent<Components::CircleCollider>(16.0f, 16.0f, 16.0f);
	collider.layer = static_cast<size_t>(CollideLayer::Enemy);

	entity.addComponent<Components::EnemyTag>();
	auto texture = game.assets->textures.load(AssetPathes::shipsTile);

	auto gunOffset = Vector2D<float>{ 12, 32 };
	auto direction = Vector2D<float>{ 0, 1 };
	auto& gun = entity.addComponent<Components::Gun>(gunOffset, direction, 30.0f, 2.0f);
	gun.bulletSpeed = 700.0f;

	Vector2D<int> tileOffset{ 32, 64 };
	auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileOffset, tileSize);
	gfx.play = false;
	gfx.rotation = 180.0f;
	auto& stats = entity.addComponent<Components::HeroStats>();
	stats.speed = 450.0f;
	stats.health = 10.0f;
	return entity;
}
