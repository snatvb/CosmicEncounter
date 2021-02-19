#pragma once
#include "ECS.h"
#include "Geometry.h"
#include <Common.h>

namespace Components {
	struct Bullet : ECS::Component {
		enum class ExplostionType : uint8_t {
			Simple,
			Fiol
		};
		float speed;
		float damage;
		Vector2D<float> direction;
		ECS::EntityID ownerId;
		std::vector<ECS::ComponentID> ignoreEntities;

		Bullet(ECS::EntityID ownerId, Vector2D<float> direction, float speed, float damage)
			: ownerId(ownerId), direction(direction), speed(speed), damage(damage) {}
	};
}
