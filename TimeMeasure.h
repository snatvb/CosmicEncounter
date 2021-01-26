#pragma once
#include <iostream>
#include <chrono>

template<typename _Period>
class TimeMesure {
public:
	TimeMesure(const char* name) : _name(name) {}

	void showDiff() {
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, _Period> delta = now - _lastTime;
		_lastTime = now;
		std::cout << _name << " " << delta.count() << std::endl;
	}

	void init() {
		_lastTime = std::chrono::high_resolution_clock::now();
	}
private:
	std::chrono::steady_clock::time_point _lastTime;
	const char* _name;
};
