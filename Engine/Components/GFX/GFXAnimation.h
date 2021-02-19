#pragma once
#include "ECS.h"
#include "SDL.h"
#include "Geometry.h"

namespace Components {
	struct GFXAnimtion : ECS::Component {
		static const int FPS = 60;
		char layer = static_cast<char>(Engine::Layer::Default);
		SDL_Texture* texture;
		float speed = 1;
		Vector2D<int> frames;
		Vector2D<int> currentFrame;
		int rows = 1;
		Size tileSize;
		Vector2D<int> offset;
		double frameCooldown = 0.0;
		bool play = true;
		bool loop = true;
		float rotation = 0;

		GFXAnimtion(SDL_Texture& texture, const Size& tileSize, Vector2D<int>& frames)
			: texture(&texture), tileSize(tileSize), frames(frames), currentFrame(1, 1)
		{}

		GFXAnimtion(SDL_Texture& texture, Size& tileSize)
			: texture(&texture), tileSize(tileSize), frames(1, 1), play(false), currentFrame(1, 1)
		{}

		GFXAnimtion(SDL_Texture& texture, Vector2D<int>& offset, Size& tileSize)
			: texture(&texture), tileSize(tileSize), offset(offset), play(false), frames(1, 1), currentFrame(1, 1)
		{}
	};

	struct GFXDestroyByEndAnimationTag : ECS::Component {};
}
