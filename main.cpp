#include <iostream>
#include "ECS.h"
#include "Engine/Engine.h"
#include "Game/Components/Components.h"
#include "Game/Systems/Systems.h"
#include "Geometry.h"
#include "TimeMeasure.h"

inline ECS::Entity& makePlayer(ECS::World& world, Engine::Game& game) {
	auto& entity = world.newEntity();
	entity.addComponent<Components::Position>(10, 10);
	entity.addComponent<Components::Scale>(20, 20);
	entity.addComponent<Components::PlayerTag>();
	auto* texture = game.assets->textures.load("Assets/Ships/tile.png");

	auto tileSize = Size{ 32, 32 };
	entity.addComponent<Components::GFXTexture>(*texture, tileSize);
	auto& stats = entity.addComponent<Components::HeroStats>();
	stats.speed = 300;
	return entity;
}

inline void makeFire(ECS::World& world, Engine::Game& game, ECS::Entity& parent) {
	auto& entity = world.newEntity();
	entity.addComponent<Components::Position>(100, 100);

	auto* texture = game.assets->textures.load("Assets/Fire/Small_Iceball_9x24_top.png");
	Size tileSize{ 9, 24 };
	Vector2D<int> frames{ 10, 6 };
	auto& animtion = entity.addComponent<Components::GFXAnimtion>(*texture, tileSize, frames);
	animtion.speed = 0.5;

	Vector2D<int> fireOffset{ 6, 18 };
	entity.addComponent<Components::Anchor>(parent.id, fireOffset);
}

class Worker : public Engine::Worker {
	inline void init() override {
		auto& game = Engine::Game::GetInstance();
		auto& world = getWorld();
		auto& player = makePlayer(world, game);
		makeFire(world, game, player);
		world.registerSystem<Systems::Input>();
		world.registerSystem<Systems::Anchor>();
		world.registerSystem<Systems::GFXAnimationRenderer>();
		world.registerSystem<Systems::GFXTextureRenderer>();
		world.registerSystem<Systems::GFXRectRenderer>();
		world.registerSystem<Systems::Remover>();
	}

	inline void update() override {
	}
};

int test() {
	static int x = 0;
	return ++x;
}

int main() {
	auto& game = Engine::Game::GetInstance();
	Worker worker;
	game.init(worker);

	game.run();
	return 0;
}
