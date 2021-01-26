#pragma once
#include <optional>
#include "ECS.h"
#include "SDL.h"
#include "../Common.h"
#include "./GFX/GFXAnimation.h"

namespace Components {
	struct GFXTag : ECS::Component {
		Engine::Layer layer;

		GFXTag() : layer(Engine::Layer::Default) {}
		GFXTag(Engine::Layer layer) : layer(layer) {}
	};

	struct GFXShape : ECS::Component {
		SDL_Color color;

		GFXShape(SDL_Color& color) : color(color) {}
	};

	struct GFXRect : GFXShape {
		GFXRect(SDL_Color& color) : GFXShape(color) {}
	};

	struct GFXCircle : GFXShape {
		GFXCircle(SDL_Color& color) : GFXShape(color) {}
	};
}
