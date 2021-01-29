#pragma once
#include "ECS.h"

namespace Components {
	struct PlayerTag : ECS::Component {};
	struct ToRemoveTag : ECS::Component {};
	struct StarTag : ECS::Component {};
}
