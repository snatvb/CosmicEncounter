#include "ControlPlayer.h"
#include "../Assets.h"

inline void createBullet(ECS::World& world, Components::Point& point) {
	Size tileSize{ 9, 15 };
	auto& game = Engine::Game::GetInstance();
	auto& entity = world.newEntity();
	entity.addComponent<Components::Transform>(point, tileSize);
	entity.addComponent<Components::Bullet>(500.0f, 10.0f);

	auto texture = game.assets->textures.load(Assets::bullets);
	entity.addComponent<Components::GFXTexture>(*texture, tileSize);
}

inline void move(ECS::Entity& entity, int x, int y, double delta) {
	auto& position = entity.getComponent<Components::Transform>().position;
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

	if (keyboard.isPressed(SDLK_SPACE)) {
		auto& transform = entity.getComponent<Components::Transform>();
		createBullet(world, transform.position);
	}

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
	void ControlPlayer::init()
	{
		_game = &Engine::Game::GetInstance();
	}

	void ControlPlayer::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			handleMove(*_world, *_game, *entity);
		}
	}
}
