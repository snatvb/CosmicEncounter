#pragma once

namespace ECS {
	class Entity;

	struct Component {
	protected:
		enum class Type {
			Simple,
			OneFrame
		};

		virtual Type _getType() {
			return Type::Simple;
		}

		friend class Entity;
	};

	struct OneFrameComponent : Component {
		virtual Type _getType() override {
			return Type::OneFrame;
		}
	};
}
