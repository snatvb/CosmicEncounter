#include "StandartEnemy.h"
#include "ControlPlayer.h"
#include "Utils/vectors.cpp"
#include "../Builders.h"

void Systems::StandartEnemy::init()
{
	_game = &Engine::Game::GetInstance();
	_playerFilter = _world->getSystemFilter<ControlPlayer>();
}

inline void shot(ECS::World& world, Engine::Game& game, ECS::Entity& player, ECS::Entity& entity) {
	auto& playerTransform = player.getComponent<Components::Transform>();
	auto& transform = entity.getComponent<Components::Transform>();
	auto& gun = entity.getComponent<Components::Gun>();

	float diffX = transform.position.x - playerTransform.position.x;
	if (diffX < 2.0f && diffX > -2.0f) {
		if (gun.cooldown <= 0) {
			auto position = transform.position + gun.offset;
			Builders::createSimpleBullet(world, gun, position);
			gun.cooldown = static_cast<int>(1000 / gun.fireRate);
		}
	}

	if (gun.cooldown > 0) {
		gun.cooldown -= static_cast<int>(game.time.deltaMs());
	}
}

inline void followPlayer(Engine::Game& game, ECS::Entity& player, ECS::Entity& entity) {
	auto& playerTransform = player.getComponent<Components::Transform>();
	auto& transform = entity.getComponent<Components::Transform>();
	auto& stats = entity.getComponent<Components::HeroStats>();

	auto diffX = transform.position.x - playerTransform.position.x;
	if (diffX > 1.0f) {
		transform.position.x -= static_cast<int>(stats.speed * game.time.delta());
	}
	if (diffX < 1.0f) {
		transform.position.x += static_cast<int>(stats.speed * game.time.delta());
	}
}

void Systems::StandartEnemy::run()
{
	for (auto entity : *filter.entities) {
		if (entity->hasComponent<Components::Collided>()) {
			auto& transform = entity->getComponent<Components::Transform>();
			Builders::createSimpleExplosion(*_world, transform);
			//entity->addComponent<Components::ToRemoveTag>();
			//return;
		}
		//transform.position.y += static_cast<int>(stats.speed * _game->time.delta());

		auto& players = _world->filterEntities(*_playerFilter);
		if (auto player = head(players)) {
			followPlayer(*_game, *player, *entity);

			if (entity->hasComponent<Components::Gun>()) {
				shot(*_world, *_game, *player, *entity);
			}
		}
	}
}
