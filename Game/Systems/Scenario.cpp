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
}
