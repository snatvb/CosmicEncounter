#pragma once
#include "SDL.h"
#undef main
#include "Common.h"
#include "Worker.h"
#include "Keyboard.h"
#include "Assets.h"
#include "EngineTime.h"
#include "Renderer.h"


namespace Engine {
	class Keyboard;
	class Time;
	class Worker;

	class Game {
	public:
#pragma region Singletone
		Game(Game const&) = delete;
		void operator=(Game const&) = delete;

		static Game& GetInstance();
#pragma endregion

		Keyboard keyboard;
		Time time;
		Assets::Manager* assets = nullptr;

		inline static Renderer* GetRenderer() {
			return GetInstance()._renderer;
		}

		inline static std::pair<int, int> GetWindowSize() {
			int width;
			int height;
			SDL_GetWindowSize(GetInstance().getWindow(), &width, &height);
			return std::pair<int, int>{width, height};
		}

		inline static void GetWindowSize(Game& game, int& width, int& height) {
			SDL_GetWindowSize(GetInstance().getWindow(), &width, &height);
		}

		void setName(const char* name);
		void init(Worker& gameHandler);
		void run();

		SDL_Renderer* getSDLRenderer();
		SDL_Window* getWindow();
		const SDL_Event& getEvent();

	private:
		Game();
		~Game();

		bool _isRunning = false;
		int _fps = 300;
		int _frameDelay = 1000 / _fps;
		const char* _name = "Engine";
		SDL_Window* _window = nullptr;
		SDL_Renderer* _sdlRenderer = nullptr;
		Renderer* _renderer = nullptr;
		Worker* _worker = nullptr;
		SDL_Event _event{};

		void _initWindow();
		void _initRenderer();
		void _initAssetsManager();
		void _handleEvents();
	};
}
