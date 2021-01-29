#pragma once

#include "./default_includes.h"

namespace Builders {
	ECS::Entity& createEnemy(ECS::World& world, Engine::Game& game, Components::Transform::Position& position);
}