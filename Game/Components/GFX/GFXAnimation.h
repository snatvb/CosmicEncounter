#pragma once
#include "ECS.h"
#include "SDL.h"
#include "Geometry.h"

namespace Components {
	struct GFXAnimtion : ECS::Component {
		SDL_Texture* texture;
		float speed = 1;
		int frames;
		int rows = 1;
		Size tileSize;
		Vector2D<int> offset;

		GFXAnimtion(SDL_Texture& texture, Size& tileSize, int frames)
			: texture(&texture), tileSize(tileSize), frames(frames)
		{}
	};
}
