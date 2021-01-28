#include "EnemySpawner.h"

constexpr int YPOS = -200;

void Systems::EnemySpawner::run()
{
	if (filter.entities->size() >= 3) {
		return;
	}

	const auto needSpawn = rand() % 100 <= 30;
	if (needSpawn) {
		int width;
		int height;
		auto& game = Engine::Game::GetInstance();
		Engine::Game::GetWindowSize(game, width, height);

		Components::Transform::Position position{
			GET_RANDOM(-100.0f, width + 100.0f),
			YPOS
		};
		auto& enemy = Builders::createEnemy(*_world, game, position);
		auto& stats = enemy.getComponent<Components::HeroStats>();
		stats.speed = stats.speed + GET_RANDOM(0, 100);
		stats.speed -= GET_RANDOM(0, 100);
	}
}
