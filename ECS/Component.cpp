#include "Component.h"

namespace ECS {
	ComponentType Component::_getType() {
		return ComponentType::Simple;
	}

	bool componentIs(Component& component, ComponentType type)
	{
		return component._getType() == type;
	}

	ComponentType OneFrameComponent::_getType() {
		return ComponentType::OneFrame;
	}
}
