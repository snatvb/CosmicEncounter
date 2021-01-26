#pragma once
#include <cmath>
#include <type_traits>
#include "api.h"

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif // !M_PI


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

	Vector2D operator+ (Vector2D& v2) {
		return Vector2D(
			x + v2.x,
			y + v2.y
		);
	};

	Vector2D operator- (Vector2D& v2) {
		return Vector2D(
			x - v2.x,
			y - v2.y
		);
	};

	Vector2D& operator+=(Vector2D& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2D& operator-=(Vector2D& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2D operator+(T s) {
		return Vector2D(x + s, y + s);
	}

	Vector2D operator-(T s) {
		return Vector2D(x - s, y - s);
	}

	Vector2D operator*(T s) {
		return Vector2D(x * s, y * s);
	}

	Vector2D operator/(T s) {
		return Vector2D(x / s, y / s);
	}

	Vector2D& operator*=(T s) {
		x *= static_cast<T>(s);
		y *= static_cast<T>(s);
		return *this;
	}

	Vector2D& operator/=(double s) {
		x /= static_cast<T>(s);
		y /= static_cast<T>(s);
		return *this;
	}

	bool operator==(const Vector2D& v) const {
		return x == v.x && y == v.y;
	}

	void set(T x, T y) {
		this->x = x;
		this->y = y;
	}

	void rotate(double deg) {
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = static_cast<T>(tx);
		y = static_cast<T>(ty);
	}

	Vector2D& normalize() {
		if (length() == 0) {
			return *this;
		};
		*this *= static_cast<T>(1.0 / length());
		return *this;
	}

	inline float dist(Vector2D v) const {
		Vector2D d(v.x - x, v.y - y);
		return d.length();
	}

	inline float length() const {
		return static_cast<float>(std::sqrt(x * x + y * y));
	}

	void truncate(double length) {
		float angle = atan2f(
			static_cast<float>(y),
			static_cast<float>(x)
		);
		x = static_cast<T>(length * cos(angle));
		y = static_cast<T>(length * sin(angle));
	}

	Vector2D ortho() const {
		return Vector2D(y, x * -1);
	}

	static float dot(Vector2D v1, Vector2D v2) {
		return static_cast<float>(v1.x * v2.x + v1.y * v2.y);
	}

	static float cross(Vector2D v1, Vector2D v2) {
		return static_cast<float>((v1.x * v2.y) - (v1.y * v2.x));
	}
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

