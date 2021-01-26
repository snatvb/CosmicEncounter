#include "Keyboard.h"
#include "Debug.h"

namespace Engine {
	SDL_KeyboardEvent& Keyboard::getEvent()
	{
		return _event;
	}

	bool Keyboard::isPressed(SDL_Keycode keycode)
	{
		return _keypressed[keycode];
	}

	void Keyboard::_handleEvent(SDL_Event& event)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			_event = event.key;
			_keypressed[event.key.keysym.sym] = true;
			break;

		case SDL_KEYUP:
			_event = SDL_KeyboardEvent();
			_keypressed[event.key.keysym.sym] = false;
			break;

		default:
			break;
		}
	}
}
