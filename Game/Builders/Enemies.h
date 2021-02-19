#pragma once

#include "./default_includes.h"

namespace Builders {
	ECS::Entity& createStandartEnemy(ECS::World& world, Engine::Game& game, Components::Transform::Position& position);
	ECS::Entity& createBombardirEnemy(ECS::World& world, Engine::Game& game, Components::Transform::Position& position);
	ECS::Entity& createTechBoss(ECS::World& world, Engine::Game& game, const Components::Transform::Position& position);
}