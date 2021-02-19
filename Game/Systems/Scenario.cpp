#include "Scenario.h"

using namespace Components;

inline Scenario* createTechScenario() {
	auto scenario = new Scenario();
	scenario->maxEnemies[Scenario::EnemyType::Standart] = 3;
	scenario->maxEnemies[Scenario::EnemyType::Bombardir] = 1;

	scenario->needKillsToBoss[Scenario::EnemyType::Bombardir] = 3;
	scenario->needKillsToBoss[Scenario::EnemyType::Standart] = 8;

	return scenario;
}

void Systems::Scenario::init()
{
	auto* scenario = createTechScenario();
	auto& entity = _world->newEntity();
	entity.addComponent(scenario);

	Builders::createTechBoss(*_world, Engine::Game::GetInstance(), { 0, 0 });
}

void Systems::Scenario::run()
{
	auto entity = filter.entities->front();

	auto& scenario = entity->getComponent<Components::Scenario>();

	// TODO: handle scenario change
	for (auto* enemyEntity : *enemiesCollided.entities) {
		_handleKills(*enemyEntity, scenario);
	}
}

void Systems::Scenario::_handleKills(const ECS::Entity& enemyEntity, Components::Scenario& scenario)
{
	auto& collided = enemyEntity.getComponent<Collided>();
	auto& enemy = enemyEntity.getComponent<Enemy>();
	auto& enemyStats = enemyEntity.getComponent<HeroStats>();
	// skip alive enemy
	if (enemyStats.health > 0) { return; }
	if (auto collidedEntity = _world->getEntityById(collided.entityId)) {
		if (auto bullet = collidedEntity->tryGetComponent<Bullet>()) {
			if (auto bulletOwner = _world->getEntityById(bullet->ownerId)) {
				if (bulletOwner->hasComponent<PlayerTag>()) {
					scenario.kills[enemy.type] += 1;

					// TODO: only in debug
					auto count = std::to_string(static_cast<int>(scenario.kills[enemy.type]));
					Engine::Debug::Log("Kills:", count);
				}
			}
		}
	}
}
