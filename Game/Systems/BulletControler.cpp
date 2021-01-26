#include "BulletControler.h"


void Systems::BulletControl::init()
{
	_game = &Engine::Game::GetInstance();
}

void Systems::BulletControl::run(ECS::FilteredEntities& entities)
{
	for (auto entity : entities) {
		auto& transform = entity->getComponent<Components::Transform>();
		auto& bullet = entity->getComponent<Components::Bullet>();
		auto diff = (bullet.direction * bullet.speed) * _game->time.delta();
		transform.position += diff;

		if (entity->hasComponent<Components::Collided>()) {
			_world->removeEntity(*entity);
		}

		int width;
		int height;
		SDL_GetWindowSize(_game->getWindow(), &width, &height);
		if (
			transform.position.x < 0
			|| transform.position.x > width
			|| transform.position.y < 0
			|| transform.position.y > height
		) {
			_world->removeEntity(*entity);
		}
	}
}
