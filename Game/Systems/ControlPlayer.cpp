#include "ControlPlayer.h"
#include "../Assets.h"
#include "../Builders.h"

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

inline void handleFire(ECS::World& world, Engine::Game& game, ECS::Entity& entity) {
	if (!entity.hasComponent<Components::Gun>()) { return; }

	auto& gun = entity.getComponent<Components::Gun>();
	auto& transform = entity.getComponent<Components::Transform>();
	if (gun.cooldown <= 0) {
		if (game.keyboard.isPressed(SDLK_SPACE)) {
			auto position = transform.position + gun.offset;
			Builders::createSimpleBullet(world, gun, position);
			gun.cooldown = static_cast<int>(1000 / gun.fireRate);
		}
	}
	else {
		gun.cooldown -= static_cast<int>(game.time.deltaMs());
	}
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

inline void handleCollide(ECS::World& world, Engine::Game& game, ECS::Entity& entity) {
	if (!entity.hasComponent<Components::Collided>()) {
		return;
	}

	auto& collided = entity.getComponent<Components::Collided>();
	auto& stats = entity.getComponent<Components::HeroStats>();
	if (auto collidedEntity = world.getEntityById(collided.entityId)) {
		if (collidedEntity->hasComponent<Components::Bullet>()) {
			auto& bullet = collidedEntity->getComponent<Components::Bullet>();
			stats.health -= bullet.damage;
		}
	}

	if (stats.health <= 0) {
		entity.addComponent<Components::ToRemoveTag>();
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
			handleFire(*_world, *_game, *entity);
			handleCollide(*_world, *_game, *entity);
		}
	}
}
