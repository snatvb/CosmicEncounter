#include "StarsControl.h"

constexpr int STARS_COUNT = 50;
constexpr int STARS_SPEED = 300;
const Vector2D<int, int> TILE_SIZE{ 8, 8 };
const Vector2D<int, int> TILE_COUNT{ 4, 2 };

inline float getRandomSpeed() {
	return rand() % 100 + STARS_SPEED - 50;
}

void Systems::StarsControl::init()
{
	auto [width, height] = Engine::Game::GetWindowSize();
	for (size_t i = 0; i < STARS_COUNT; i++) {
		Components::Transform::Position position{
			static_cast<float>(rand() % width),
			static_cast<float>(rand() % height)
		};
		Vector2D<int, int> tileOffset{
			(rand() % TILE_COUNT.x) * TILE_SIZE.x,
			(rand() % TILE_COUNT.y) * TILE_SIZE.y
		};
		Builders::createStar(*_world, tileOffset, position, getRandomSpeed());
	}
}

void Systems::StarsControl::run() {
	for (auto entity : *filter.entities) {
		auto& transform = entity->getComponent<Components::Transform>();
		auto& star = entity->getComponent<Components::Star>();

		auto deltaTime = Engine::Game::GetInstance().time.delta();
		transform.position.y += static_cast<float>(star.speed * deltaTime);

		auto [width, height] = Engine::Game::GetWindowSize();
		if (transform.position.y > height) {
			transform.position.y = 0;
			transform.position.x = static_cast<float>(rand() % width);
			star.speed = getRandomSpeed();
		}
	}
}
