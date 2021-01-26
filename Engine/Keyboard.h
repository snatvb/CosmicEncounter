#pragma once
#include <map>
#include "SDL.h"

namespace Engine {
	class Game;

	class Keyboard {
	public:
		SDL_KeyboardEvent& getEvent();
		bool isPressed(SDL_Keycode keycode);

	private:
		std::map<SDL_Keycode, bool> _keypressed;
		SDL_KeyboardEvent _event;

		void _handleEvent(SDL_Event& event);

		friend class Game;
	};
}
