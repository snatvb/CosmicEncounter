#include "Game.h"
#include "Debug.h"

namespace Engine {
	Game::Game() {}
	Game::~Game() {}

	Game& Game::GetInstance()
	{
		static Game instance;
		return instance;
	}

	void Game::setName(const char* name)
	{
		_name = name;
	}

	void Game::init(Worker& worker)
	{
		_worker = &worker;
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
			_initWindow();
			_initRenderer();
			_initAssetsManager();
			worker.init();
			_isRunning = true;
		}
	}

	void Game::run()
	{
		Uint32 frameStart;
		int frameTime;

		while (_isRunning) {
			frameStart = SDL_GetTicks();
			frameTime = SDL_GetTicks() - frameStart;


			SDL_RenderClear(_renderer);
			_handleEvents();
			_worker->getWorld().update();
			_worker->update();
			SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
			SDL_RenderPresent(_renderer);

			if (_frameDelay > frameTime) {
				SDL_Delay(_frameDelay - frameTime);
			}
		}
	}

	SDL_Renderer* Game::getRenderer()
	{
		return _renderer;
	}

	SDL_Window* Game::getWindow()
	{
		return _window;
	}

	const SDL_Event& Game::getEvent()
	{
		return _event;
	}

	void Game::_initWindow()
	{
		_window = SDL_CreateWindow(
			_name,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800,
			800,
			0 // flag
		);

		if (_window) {
			Debug::Log("Window created");
		}
	}

	void Game::_initRenderer()
	{
		_renderer = SDL_CreateRenderer(_window, -1, 0);

		if (_renderer) {
			SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
			Debug::Log("Renderer initialized");
		}
	}

	void Game::_initAssetsManager()
	{
		assets = new Assets::Manager(*_renderer);
	}

	void Game::_handleEvents()
	{
		while (SDL_PollEvent(&_event)) {
			keyboard._handleEvent(_event);

			switch (_event.type)
			{
			case SDL_QUIT:
				_isRunning = false;
				break;

			default:
				break;
			}
		}
	}
}
