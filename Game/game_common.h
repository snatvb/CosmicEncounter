#pragma once
#include "./Components.h"

enum class CollideLayer : size_t {
	Bullet = Components::DEFAULT_COLLIDER_LAYER - 2,
	Enemy = Components::DEFAULT_COLLIDER_LAYER - 1,
	Default = Components::DEFAULT_COLLIDER_LAYER,
	Player = Components::DEFAULT_COLLIDER_LAYER + 1,
};
