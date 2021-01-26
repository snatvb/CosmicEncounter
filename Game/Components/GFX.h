#pragma once
#include "ECS.h"
#include "SDL.h"

namespace Components {
	struct GFX : ECS::Component {
		SDL_Color color;

		GFX(SDL_Color& color) : color(color) {}
	};

	struct GFXRect : GFX {
		GFXRect(SDL_Color& color) : GFX(color) {}
	};

	struct GFXCircle : GFX {
		GFXCircle(SDL_Color& color) : GFX(color) {}
	};
}
