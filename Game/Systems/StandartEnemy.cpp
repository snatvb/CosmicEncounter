#include "StandartEnemy.h"

void Systems::StandartEnemy::init()
{
	_game = &Engine::Game::GetInstance();
}

void Systems::StandartEnemy::run(ECS::FilteredEntities& entities)
{
	for (auto entity : entities) {
		auto& transform = entity->getComponent<Components::Transform>();
		auto& stats = entity->getComponent<Components::HeroStats>();
		transform.position.y += static_cast<int>(stats.speed * _game->time.delta());

		if (entity->hasComponent<Components::Collided>()) {
			entity->addComponent<Components::ToRemoveTag>();
		}
	}
}
