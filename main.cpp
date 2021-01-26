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

class Worker : public Engine::Worker {
	inline void init() override {
		auto& game = Engine::Game::GetInstance();
		auto& world = getWorld();
		makePlayer(world, game);
		world.registerSystem<Systems::GFXRectRenderer>();
		world.registerSystem<Systems::GFXTextureRenderer>();
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
