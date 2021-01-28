#pragma once

#include <random>
#define GET_RANDOM(min, max) \
	rand() % max + min

namespace helpers {
	void srandTime();
}
