#include "InputSystem.h"

inline void move(ECS::Entity& entity, int x, int y) {
	auto& position = entity.getComponent<Components::Position>();
	auto& stats = entity.getComponent<Components::HeroStats>();

	position.x += (int)(x * stats.speed);
	position.y += (int)(y * stats.speed);
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

namespace Systems {
	void Input::init()
	{
		_game = &Engine::Game::GetInstance();
	}

	void Input::run(ECS::FilteredEntities& entities)
	{

		for (auto& entity : entities) {
			_handleMove(*entity);
		}
	}

	void Input::_handleMove(ECS::Entity& entity)
	{
		auto& keyboard = _game->keyboard;
		int x = getX(keyboard);
		int y = getY(keyboard);

		if (x != 0 || y != 0) {
			move(entity, x, y);
		}
	}
}
