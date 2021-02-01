#pragma once
#include "ECS.h"
#include "Geometry.h"

namespace Components {
	struct Bullet : ECS::Component {
		float speed;
		float damage;
		Vector2D<float> direction;
		ECS::EntityID ownerId;

		Bullet(ECS::EntityID ownerId, Vector2D<float> direction, float speed, float damage)
			: ownerId(ownerId), direction(direction), speed(speed), damage(damage) {}
	};
}
