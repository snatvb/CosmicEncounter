#pragma once
#include "ECS.h"

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
}
