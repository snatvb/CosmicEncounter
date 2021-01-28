#include "StandartEnemy.h"
#include "ControlPlayer.h"
#include "Utils/vectors.cpp"
#include "../Builders.h"

void Systems::StandartEnemy::init()
{
	_game = &Engine::Game::GetInstance();
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

inline bool hasAllyForward(ECS::Entity& entity, Components::Transform& transform, ECS::FilteredEntities& otherEntities) {
	for (auto other : otherEntities) {
		if (other->id == entity.id) { continue; }
		auto& otherPosition = other->getComponent<Components::Transform>().position;
		auto otherDiffY = otherPosition.y - transform.position.y;
		if (otherDiffY < 50 && otherDiffY > 0) {
			return true;
		}
	}
	return false;
}

inline void followPlayer(
	Engine::Game& game,
	ECS::Entity& player,
	ECS::Entity& entity,
	ECS::FilteredEntities& otherEntities
) {
	auto& playerTransform = player.getComponent<Components::Transform>();
	auto& transform = entity.getComponent<Components::Transform>();
	auto& stats = entity.getComponent<Components::HeroStats>();
	const auto deltaTime = game.time.delta();

	auto diffX = transform.position.x - playerTransform.position.x;
	if (diffX > 1.0f) {
		transform.position.x -= static_cast<int>(stats.speed * deltaTime);
	}
	if (diffX < 1.0f) {
		transform.position.x += static_cast<int>(stats.speed * deltaTime);
	}

	auto diffY = transform.position.y - playerTransform.position.y;
	if (ABS(diffY) > 300) {
		if(!hasAllyForward(entity, transform, otherEntities)) {
			transform.position.y += stats.speed * deltaTime;
		}
	}
}

void Systems::StandartEnemy::run()
{
	for (auto entity : *filter.entities) {
		auto& stats = entity->getComponent<Components::HeroStats>();
		if (auto collided = entity->tryGetComponent<Components::Collided>()) {
			if (auto entityCollided = _world->getEntityById(collided->entityId)) {
				if (auto bullet = entityCollided->tryGetComponent<Components::Bullet>()){
					stats.health -= bullet->damage;
				}
			}
		}

		if (auto player = head(*playerFilter.entities)) {
			followPlayer(*_game, *player, *entity, *filter.entities);

			if (entity->hasComponent<Components::Gun>()) {
				shot(*_world, *_game, *player, *entity);
			}
		}
	}
}
