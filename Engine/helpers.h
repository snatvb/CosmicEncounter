#pragma once

#include <random>
#define GET_RANDOM(min, max) \
	rand() % max + min

#define ABS(x) (((x) < 0) ? (-x) : (x))

namespace Engine {
	namespace helpers {
		void srandTime();
	}
}
