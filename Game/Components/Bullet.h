#pragma once
#include "ECS.h"
#include "Geometry.h"

namespace Components {
	struct Bullet : ECS::Component {
		float speed;
		float damage;
		Vector2D<float> direction;

		Bullet(Vector2D<float> direction, float speed, float damage)
			: direction(direction), speed(speed), damage(damage) {}
	};
}
