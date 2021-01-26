#pragma once
#include <optional>
#include "ECS.h"
#include "SDL.h"
#include "./GFX/GFXAnimation.h"

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

	struct GFXTexture : ECS::Component {
		SDL_Texture* texture;
		Vector2D<int> offset;
		std::optional<Size> tileSize;

		GFXTexture(SDL_Texture& texture)
			: texture(&texture) {}

		GFXTexture(SDL_Texture& texture, Size& tileSize)
			: texture(&texture), tileSize(tileSize) {}

		GFXTexture(SDL_Texture& texture, Vector2D<int>& offset, Size& tileSize)
			: texture(&texture), offset(offset), tileSize(tileSize) {}
	};
}
