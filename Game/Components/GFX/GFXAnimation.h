#pragma once
#include "ECS.h"
#include "SDL.h"

namespace Components {
	struct GFXAnimtion : ECS::Component {
		SDL_Texture* texture;
		float speed;

	};
}
