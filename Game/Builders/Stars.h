#pragma once

#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"
#include "../AssetPathes.h"

namespace Builders {
	void createStar(ECS::World& world, Vector2D<int>& offset, Components::Transform::Position& position, float speed = 0.0f);
}

