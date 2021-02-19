#pragma once
#include "ECS.h"

namespace Components {
	struct Enemy : ECS::Component {
		enum class Type {
			Standart,
			Bombardir,
			__count
		};

		Type type;

		Enemy(Type type) : type(type) {}
	};

	struct TechBoss : ECS::Component {
		const float fireRate = 1.0f;
	};
}

