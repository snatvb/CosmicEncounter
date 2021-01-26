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

	struct GFXRect : GFXShape {
		GFXRect(SDL_Color& color) : GFXShape(color) {}
	};

	struct GFXCircle : GFXShape {
		GFXCircle(SDL_Color& color) : GFXShape(color) {}
	};
}
