#pragma once

#include <array>

template<typename E, class T, std::size_t N>
class EnumArray : public std::array<T, N> {
public:
	T& operator[] (E e) {
		return std::array<T, N>::operator[]((std::size_t)e);
	}

	const T& operator[] (E e) const {
		return std::array<T, N>::operator[]((std::size_t)e);
	}
};
