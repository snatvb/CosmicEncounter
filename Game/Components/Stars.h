#pragma once
#include "ECS.h"

namespace Components {
	struct Star : ECS::Component {
		float speed;

		Star(float speed) : speed(speed) {}
	};
}
