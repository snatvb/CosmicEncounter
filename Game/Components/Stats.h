#pragma once
#include "ECS.h"

namespace Components {
	struct HeroStats : ECS::Component {
		float health;
		float speed;
	};
}
