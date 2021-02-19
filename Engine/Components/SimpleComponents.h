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

		Anchor(ECS::EntityID entityId)
			: entityId(entityId), rotationCenter(-1, -1) {}
		Anchor(ECS::EntityID entityId, Vector2D<int>& offset)
			: entityId(entityId), offset(offset), rotationCenter(-1, -1) {}
	};

	struct Transform : ECS::Component {
		using Position = Vector2D<float>;
		using Rotation = float;
		using Scale = Size;

		Scale scale;
		Position position;
		Rotation rotation = 0.0f;

		Transform() = default;
		Transform(float x, float y) : position(x, y) {}
		Transform(const Position& position) : position(position) {}
		Transform(const Position& position, Scale& scale)
			: position(position), scale(scale) {}
		Transform(const Position& position, Rotation rotation)
			: position(position), rotation(rotation) {}
		Transform(const Position& position, Scale& scale, Rotation rotation)
			: position(position), rotation(rotation), scale(scale) {}
		Transform(const Position& position, Rotation rotation, Scale& scale)
			: position(position), rotation(rotation), scale(scale) {}
	};
}
