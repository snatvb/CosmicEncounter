#pragma once
#include "ECS.h"
#include "Geometry.h"

namespace Components {
	using Point = Vector2D<float>;

	struct CircleCollider : ECS::Component {
		Point center;
		float radius;

		CircleCollider() {}
		CircleCollider(Point& center, float radius)
			: center(center), radius(radius) {}
	};
}
