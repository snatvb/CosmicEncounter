#include <iostream>
#include <stdint.h>
#include "ECS.h"
#include "Engine/Engine.h"
#include "Game/Components/Components.h"
#include "Game/Systems/Systems.h"
#include "Geometry.h"
#include "Game/AssetPathes.h"
#include "TimeMeasure.h"

inline ECS::Entity& createPlayer(ECS::World& world, Engine::Game& game) {
	auto& entity = world.newEntity();
	auto position = Components::Transform::Position(300, 700);
	auto tileSize = Size{ 32, 32 };
	entity.addComponent<Components::Transform>(position, tileSize);
	entity.addComponent<Components::PlayerTag>();
	
	auto& collider = entity.addComponent<Components::CircleCollider>(16.0f, 16.0f, 16.0f);
	collider.layer = static_cast<size_t>(CollideLayer::Player);

	auto gunOffset = Vector2D<float>{ 12, -16 };
	auto direction = Vector2D<float>{ 0, -1 };
	auto& gun = entity.addComponent<Components::Gun>(gunOffset, direction, 10.0f, 3.0f);
	gun.bulletSpeed = 1500.0f;

	auto texture = game.assets->textures.load("Assets/Ships/tile.png");
	auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileSize);
	gfx.play = false;
	auto& stats = entity.addComponent<Components::HeroStats>();
	stats.speed = 900.0f;
	stats.health = 30.0f * 100000;
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
		world.registerSystem<Systems::EnemySpawner>();
		world.registerSystem<Systems::StarsControl>();
		world.registerSystem<Systems::Collide>();
		world.registerSystem<Systems::ControlPlayer>();
		world.registerSystem<Systems::Anchor>();
		world.registerSystem<Systems::EnemyBehaviour>();
		world.registerSystem<Systems::TechBossAI>();
		world.registerSystem<Systems::BulletControl>();
		world.registerSystem<Systems::CheckDied>();
		world.registerSystem<Systems::Scenario>();
		world.registerSystem<Systems::Remover>();
		world.registerSystem<Systems::EndAnimationRemover>();
		world.registerSystem<Systems::GFXAnimationRenderer>();
		world.registerSystem<Systems::GFXShapeRenderer>();
		world.init();
		auto& player = createPlayer(world, game);
		createFire(world, game, player);
	}

	inline void update() override {}
};

int main() {
	auto& game = Engine::Game::GetInstance();
	Worker worker;
	game.init(worker);

	game.run();
	return 0;
}
