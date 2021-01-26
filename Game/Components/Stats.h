#pragma once
#include "ECS.h"

namespace Components {
	struct HeroStats : ECS::Component {
		int health;
		float speed;
	};
}
