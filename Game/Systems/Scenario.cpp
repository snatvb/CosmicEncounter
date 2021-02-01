#include "Scenario.h"

using namespace Components;

inline Scenario* createTechScenario() {
	auto scenario = new Scenario();
	scenario->maxEnemies[Scenario::EnemyType::Standart] = 3;
	scenario->maxEnemies[Scenario::EnemyType::Bombardir] = 1;

	return scenario;
}

void Systems::Scenario::init()
{
	auto scenario = createTechScenario();
	auto& entity = _world->newEntity();
	entity.addComponent(scenario);
}

void Systems::Scenario::run()
{
	auto entity = filter.entities->front();

	auto& scenario = entity->getComponent<Components::Scenario>();

	// TODO: handle scenario change
	for (auto enemyEntity : *enemiesCollided.entities) {
		auto& collided = enemyEntity->getComponent<Collided>();
		auto& enemy = enemyEntity->getComponent<Enemy>();
		if (auto collidedEntity = _world->getEntityById(collided.entityId)) {
			if (auto bullet = collidedEntity->tryGetComponent<Bullet>()) {
				if (auto bulletOwner = _world->getEntityById(bullet->ownerId)) {
					if (bulletOwner->hasComponent<PlayerTag>()) {
						scenario.kills[enemy.type] += 1;
					}
				}
			}
		}
	}
}
