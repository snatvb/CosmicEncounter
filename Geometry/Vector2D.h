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
	Vector2D(T x, T y) : x(x), y(y) {};
};

template struct Vector2D<__int8>;
template struct Vector2D<__int16>;
template struct Vector2D<__int32>;
template struct Vector2D<int>;
template struct Vector2D<unsigned __int8>;
template struct Vector2D<unsigned __int16>;
template struct Vector2D<unsigned __int32>;
template struct Vector2D<unsigned int>;
template struct Vector2D<float>;
template struct Vector2D<double>;

