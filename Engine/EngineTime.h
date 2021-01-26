#pragma once
#include <chrono>

namespace Engine {
	class Game;

	class Time {
	public:
		double delta();
		double deltaMs();

	private:
		std::chrono::steady_clock::time_point _lastTime;
		std::chrono::duration<double> _delta;

		void _init();
		void _update();

		friend class Game;
	};
}
