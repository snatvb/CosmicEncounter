#include <iostream>
#include <stdint.h>
#include "ECS.h"
#include "Engine/Engine.h"
#include "Game/Components/Components.h"
#include "Game/Systems/Systems.h"
#include "Geometry.h"
#include "Game/Assets.h"
#include "TimeMeasure.h"

inline ECS::Entity& createPlayer(ECS::World& world, Engine::Game& game) {
	auto& entity = world.newEntity();
	auto position = Components::Transform::Position(300, 700);
	auto tileSize = Size{ 32, 32 };
	entity.addComponent<Components::Transform>(position, tileSize);
	entity.addComponent<Components::CircleCollider>(16.0f, 16.0f, 16.0f);
	entity.addComponent<Components::PlayerTag>();

	auto gunOffset = Vector2D<float>{ 12, -16 };
	auto direction = Vector2D<float>{ 0, -1 };
	auto& gun = entity.addComponent<Components::Gun>(gunOffset, direction, 10.0f, 101.0f);
	gun.bulletSpeed = 1500.0f;

	auto texture = game.assets->textures.load("Assets/Ships/tile.png");
	auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileSize);
	gfx.play = false;
	auto& stats = entity.addComponent<Components::HeroStats>();
	stats.speed = 900.0f;
	return entity;
}

inline ECS::Entity& createEnemy(ECS::World& world, Engine::Game& game) {
	auto& entity = world.newEntity();
	auto position = Components::Transform::Position(300.0f, 300.0f);
	auto tileSize = Size{ 32, 32 };
	entity.addComponent<Components::Transform>(position, tileSize);
	entity.addComponent<Components::CircleCollider>(16.0f, 16.0f, 16.0f);
	entity.addComponent<Components::EnemyTag>();
	auto texture = game.assets->textures.load("Assets/Ships/tile.png");

	auto gunOffset = Vector2D<float>{ 12, 32 };
	auto direction = Vector2D<float>{ 0, 1 };
	auto& gun = entity.addComponent<Components::Gun>(gunOffset, direction, 10.0f, 13.0f);
	gun.bulletSpeed = 1200.0f;

	Vector2D<int> tileOffset{64, 64};
	auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileOffset, tileSize);
	gfx.play = false;
	gfx.rotation = 180.0f;
	auto& stats = entity.addComponent<Components::HeroStats>();
	stats.speed = 500.0f;
	return entity;
}


inline void createFire(ECS::World& world, Engine::Game& game, ECS::Entity& parent) {
	auto& entity = world.newEntity();
	entity.addComponent<Components::Transform>();

	auto* texture = game.assets->textures.load("Assets/Fire/Small_Iceball_9x24_top.png");
	Size tileSize{ 9, 24 };
	Vector2D<int> frames{ 10, 6 };
	auto& animtion = entity.addComponent<Components::GFXAnimtion>(*texture, tileSize, frames);
	animtion.speed = 0.8f;

	Vector2D<int> fireOffset{ -4, 0 };
	auto& anchor = entity.addComponent<Components::Anchor>(parent.id, fireOffset);
	anchor.jointCenter.x = 16;
	anchor.jointCenter.y = 24;
}

class Worker : public Engine::Worker {
	inline void init() override {
		auto& game = Engine::Game::GetInstance();
		auto& world = getWorld();
		world.registerSystem<Systems::EndAnimationRemover>();
		world.registerSystem<Systems::Collide>();
		world.registerSystem<Systems::ControlPlayer>();
		world.registerSystem<Systems::Anchor>();
		world.registerSystem<Systems::StandartEnemy>();
		world.registerSystem<Systems::BulletControl>();
		world.registerSystem<Systems::Remover>();
		world.registerSystem<Systems::GFXAnimationRenderer>(_renderCache);
		//world.registerSystem<Systems::GFXRectRenderer>();
		world.init();
		auto& player = createPlayer(world, game);
		createFire(world, game, player);
		createEnemy(world, game);
	}

	inline void update() override {
		for (auto& layer : _renderCache) {
			for (auto& f : layer) {
				f();
			}
			layer.clear();
		}
	}
};

int main() {
	auto& game = Engine::Game::GetInstance();
	Worker worker;
	game.init(worker);

	game.run();
	return 0;
}
