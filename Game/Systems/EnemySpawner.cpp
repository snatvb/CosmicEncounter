#include "EnemySpawner.h"

constexpr int YPOS = -200;

using namespace Components;

void Systems::EnemySpawner::run()
{
	auto& scenario = scenarios.entities->front()->getComponent<Components::Scenario>();
	spawnStandart(scenario);
	spawnBombardir(scenario);
}

bool hasCount(ECS::FilteredEntities& entities, int needCount, Enemy::Type type) {
	int counter = 0;
	for (auto entity : entities) {
		const auto& enemy = entity->getComponent<Enemy>();
		if (enemy.type == type) {
			counter++;
		}

		if (counter >= needCount) {
			return true;
		}
	}
	return false;
}

void Systems::EnemySpawner::spawnStandart(Components::Scenario& scenario)
{
	if (hasCount(*filter.entities, scenario.maxEnemies[Enemy::Type::Standart], Enemy::Type::Standart)) {
		return;
	}

	const auto needSpawn = rand() % 1000 <= 6;
	if (needSpawn) {
		int width;
		int height;
		auto& game = Engine::Game::GetInstance();
		Engine::Game::GetWindowSize(game, width, height);

		Transform::Position position{
			GET_RANDOM(-100.0f, width + 100.0f),
			YPOS
		};
		auto& enemy = Builders::createStandartEnemy(*_world, game, position);
		auto& stats = enemy.getComponent<HeroStats>();
		stats.speed = stats.speed + GET_RANDOM(0, 100);
		stats.speed -= GET_RANDOM(0, 100);
	}
}



void Systems::EnemySpawner::spawnBombardir(Components::Scenario& scenario)
{
	if (hasCount(*filter.entities, scenario.maxEnemies[Enemy::Type::Bombardir], Enemy::Type::Bombardir)) {
		return;
	}

	const auto needSpawn = rand() % 1000 <= 6;
	if (needSpawn) {
		int width;
		int height;
		auto& game = Engine::Game::GetInstance();
		Engine::Game::GetWindowSize(game, width, height);

		Transform::Position position{
			GET_RANDOM(-100.0f, width + 100.0f),
			YPOS
		};
		auto& enemy = Builders::createBombardirEnemy(*_world, game, position);
		auto& stats = enemy.getComponent<HeroStats>();
		stats.speed = stats.speed + GET_RANDOM(0, 100);
		stats.speed -= GET_RANDOM(0, 100);
	}
}

