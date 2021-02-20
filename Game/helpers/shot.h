#pragma once

#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace helpers {
	void shotOnLine(ECS::World& world, float buffer, const std::pair<const ECS::Entity&, const ECS::Entity&>& followerTarget);
}
