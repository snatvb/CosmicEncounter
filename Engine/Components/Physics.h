#pragma once
#include <bitset>
#include "ECS.h"
#include "Geometry.h"

namespace Components {
	using Point = Vector2D<float>;

	constexpr size_t DEFAULT_COLLIDER_LAYER = 16;
	constexpr size_t LAYERS_COUNT = 32;
	struct CircleCollider : ECS::Component {
		std::bitset<LAYERS_COUNT> layers;
		size_t layer = DEFAULT_COLLIDER_LAYER;
		Point center;
		float radius;

		CircleCollider(Point& center, float radius)
			: center(center), radius(radius) {
			layers.set();
		}

		CircleCollider(float x, float y, float radius)
			: center(x, y), radius(radius) {
			layers.set();
		}
	};

	struct Collided : ECS::OneFrameComponent {
		ECS::EntityID entityId;

		Collided(ECS::EntityID id) : entityId(id) {}
	};
}
