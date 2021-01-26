#include <iostream>
#include "ECS.h"
#include "Engine/Engine.h"
#include "Game/Components/Components.h"
#include "Game/Systems/Systems.h"
#include "Geometry.h"

inline void makePlayer(ECS::World& world, Engine::Game& game) {
	auto& entity = world.newEntity();
	entity.addComponent<Components::Position>(10, 10);
	entity.addComponent<Components::Scale>(20, 20);
	entity.addComponent<Components::PlayerTag>();
	SDL_Color color{ 255, 255, 255 };
	auto* texture = game.assets->textures.load("Assets/Ships/tile.png");
	entity.addComponent<Components::GFXTexture>(color, *texture);
	auto& stats = entity.addComponent<Components::HeroStats>();
	stats.speed = 1;
}

inline void makeFire(ECS::World& world, Engine::Game& game) {
	auto& entity = world.newEntity();
	entity.addComponent<Components::Position>(100, 100);

	auto* texture = game.assets->textures.load("Assets/Fire/Small_Iceball_9x24_top.png");
	Size tileSize(9, 24);
	Vector2D<int> frames(10, 6);
	auto& animtion = entity.addComponent<Components::GFXAnimtion>(*texture, tileSize, frames);
	animtion.speed = 0.5;
}

class Worker : public Engine::Worker {
	inline void init() override {
		auto& game = Engine::Game::GetInstance();
		auto& world = getWorld();
		makePlayer(world, game);
		makeFire(world, game);
		world.registerSystem<Systems::GFXAnimationRenderer>();
		world.registerSystem<Systems::GFXTextureRenderer>();
		world.registerSystem<Systems::GFXRectRenderer>();
		world.registerSystem<Systems::Input>();
	}

	inline void update() override {
	}
};

int main() {
	auto& game = Engine::Game::GetInstance();
	Worker worker;
	game.init(worker);

	game.run();
	return 0;
}
