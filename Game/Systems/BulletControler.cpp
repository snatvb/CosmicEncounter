#include "BulletControler.h"


void Systems::BulletControl::init()
{
	_game = &Engine::Game::GetInstance();
}

void Systems::BulletControl::run()
{
	for (auto entity : *filter.entities) {
		auto& transform = entity->getComponent<Components::Transform>();
		auto& bullet = entity->getComponent<Components::Bullet>();
		auto diff = (bullet.direction * bullet.speed) * static_cast<float>(_game->time.delta());
		transform.position += diff;

		if (entity->hasComponent<Components::Collided>()) {
			auto& collided = entity->getComponent<Components::Collided>();
			if (auto entityCollided = _world->getEntityById(collided.entityId)) {
				if (!entityCollided->hasComponent<Components::Bullet>()) {
					entity->addComponent<Components::ToRemoveTag>();
				}
			}
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
			entity->addComponent<Components::ToRemoveTag>();
		}
	}
}
