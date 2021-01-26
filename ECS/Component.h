#pragma once

namespace ECS {

	enum class ComponentType {
		Simple,
		OneFrame
	};

	struct Component {

	protected:
		virtual ComponentType _getType();

		friend bool componentIs(Component& component, ComponentType type);
	};

	struct OneFrameComponent : Component {
		virtual ComponentType _getType() override;
	};
}
