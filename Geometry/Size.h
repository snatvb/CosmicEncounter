#pragma once
#include "api.h"

extern "C" struct API Size {
	int width;
	int height;

	Size();
	Size(int width, int height);
};
