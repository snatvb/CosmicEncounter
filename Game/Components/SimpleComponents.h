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
		Vector2D<int> rotationCenter;
		Vector2D<int> jointCenter;

		Anchor(ECS::EntityID entityId) : entityId(entityId) {}
		Anchor(ECS::EntityID entityId, Vector2D<int>& offset)
			: entityId(entityId), offset(offset) {}
	};

	struct Transform : ECS::Component {
		using Position = Vector2D<float>;
		using Rotation = float;
		using Scale = Size;

		Scale scale;
		Position position;
		Rotation rotation;

		Transform() {}
		Transform(float x, float y) : position(Position{ x, y }) {}
		Transform(Position& position) : position(position) {}
		Transform(Position& position, Scale& scale)
			: position(position), scale(scale) {}
		Transform(Position& position, Rotation& rotation)
			: position(position), rotation(rotation) {}
		Transform(Position& position, Scale& scale, Rotation& rotation)
			: position(position), rotation(rotation), scale(scale) {}
		Transform(Position& position, Rotation& rotation, Scale& scale)
			: position(position), rotation(rotation), scale(scale) {}
	};
}
