#pragma once
#include <optional>
#include "ECS.h"
#include "SDL.h"
#include "../Common.h"
#include "./GFX/GFXAnimation.h"

namespace Components {
	struct GFXShape : ECS::Component {
		SDL_Color color;
		Engine::Layer layer = Engine::Layer::Default;

		GFXShape(SDL_Color& color) : color(color) {}
	};

	struct GFXRect : ECS::Component {
		Size size;
		GFXRect(Size& size) : size(size) {}
	};

	struct GFXCircle : ECS::Component {
		float radius;
		GFXCircle(float radius) : radius(radius) {}
	};
}
