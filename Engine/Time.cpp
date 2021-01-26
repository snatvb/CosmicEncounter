#include "Time.h"

namespace Engine {
	double Time::delta()
	{
		return _delta.count();
	}

	void Time::_init()
	{
		_lastTime = std::chrono::high_resolution_clock::now();
	}

	void Time::_update()
	{
		auto now = std::chrono::high_resolution_clock::now();
		_delta = now - _lastTime;
		_lastTime = now;
	}
}
