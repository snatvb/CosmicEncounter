#pragma once
#include "ECS.h"
#include "Geometry.h"

namespace Components {
	using Point = Vector2D<float>;

	struct CircleCollider : ECS::Component {
		Point center;
		float radius;

		CircleCollider(Point& center, float radius)
			: center(center), radius(radius) {}

		CircleCollider(float x, float y, float radius)
			: center(x, y), radius(radius) {}
	};

	struct Collided : ECS::OneFrameComponent {
		ECS::EntityID entityId;

		Collided(ECS::EntityID id) : entityId(id) {}
	};
}
