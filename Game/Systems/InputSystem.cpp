#include "InputSystem.h"

inline void move(ECS::Entity& entity, int x, int y, double delta) {
	auto& position = entity.getComponent<Components::Position>();
	auto& stats = entity.getComponent<Components::HeroStats>();

	position.x += (int)(stats.speed * delta * x);
	position.y += (int)(stats.speed * delta * y);
}

inline int getX(Engine::Keyboard& keyboard) {
	if (keyboard.isPressed(SDLK_a)) {
		return -1;
	}

	if (keyboard.isPressed(SDLK_d)) {
		return 1;
	}

	return 0;
}

inline int getY(Engine::Keyboard& keyboard) {
	if (keyboard.isPressed(SDLK_w)) {
		return -1;
	}

	if (keyboard.isPressed(SDLK_s)) {
		return 1;
	}

	return 0;
}

inline void handleMove(ECS::World& world, Engine::Game& game, ECS::Entity& entity) {
	auto& keyboard = game.keyboard;

	if (keyboard.isPressed(SDLK_f)) {
		world.removeEntity(entity);
	}

	int x = getX(keyboard);
	int y = getY(keyboard);

	if (x != 0 || y != 0) {
		move(entity, x, y, game.time.delta());
	}
}

namespace Systems {
	void Input::init()
	{
		_game = &Engine::Game::GetInstance();
	}

	void Input::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			handleMove(*_world, *_game, *entity);
		}
	}
}
