#pragma once
#include "ECS.h"

namespace Components {
	struct Position : ECS::Component {
		int x;
		int y;

		Position() : x(0), y(0) {}
		Position(int x, int y) : x(x), y(y) {}
	};

	struct Size : ECS::Component {
		int width;
		int height;

		Size() : width(0), height(0) {}
		Size(int width, int height)
			: width(width), height(height) {}
	};
}
