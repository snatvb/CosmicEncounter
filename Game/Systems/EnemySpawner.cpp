#include "EnemySpawner.h"

constexpr int YPOS = -200;

void Systems::EnemySpawner::run()
{
	if (filter.entities->size() >= 3) {
		return;
	}

	auto needSpawn = rand() % 100 <= 30;
	if (needSpawn) {
		int width;
		int height;
		auto& game = Engine::Game::GetInstance();
		Engine::Game::GetWindowSize(game, width, height);

		Components::Transform::Position position{
			GET_RANDOM(-100.0f, width + 100.0f),
			YPOS
		};
		Builders::createEnemy(*_world, game, position);
	}
}
