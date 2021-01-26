#pragma once
#include "ECS.h"

namespace Components {
	struct Bullet : ECS::Component {
		float speed;
		float damage;

		Bullet(float spped, float damage)
			: speed(speed), damage(damage) {}
	};
}
