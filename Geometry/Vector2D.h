#pragma once
#include <type_traits>
#include "api.h"

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
struct API Vector2D
{
	T x;
	T y;

	Vector2D() : x(0), y(0) {};
	Vector2D(T x, T y) : x(x), y(0) {};
};

