#pragma once
#include "ECS.h"
#include "Geometry.h"
#include "Engine.h"

namespace Components {
	struct Gun : ECS::Component {
		enum class Type {
			Default,
			Grenade,
			Fiol
		};

		Type type = Type::Default;
		float damage;
		float bulletSpeed = 0;
		Vector2D<float> direction;
		Vector2D<float> offset;
		float fireRate; // shoots per sec
		int cooldown = 0;

		Gun(Vector2D<float> direction, float damage, float fireRate)
			: offset(0.0f, 0.0f), direction(direction), damage(damage), fireRate(fireRate) {};

		Gun(Vector2D<float> offset, Vector2D<float> direction, float damage, float fireRate)
			: offset(offset), direction(direction), damage(damage), fireRate(fireRate) {};
	};
}
