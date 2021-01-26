#pragma once
#include "ECS.h"
#include "Geometry.h"

namespace Components {
	struct Position : ECS::Component {
		int x;
		int y;

		Position() : x(0), y(0) {}
		Position(int x, int y) : x(x), y(y) {}
	};

	struct Scale : ECS::Component {
		int width;
		int height;

		Scale() : width(0), height(0) {}
		Scale(int width, int height)
			: width(width), height(height) {}
	};

	struct Anchor : ECS::Component {
		ECS::EntityID entityId;
		Vector2D<int> offset;

		Anchor(ECS::EntityID entityId) : entityId(entityId) {}
		Anchor(ECS::EntityID entityId, Vector2D<int>& offset) : entityId(entityId), offset(offset) {}
	};
}
