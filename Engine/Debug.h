#pragma once
#include <iostream>
#include <string>

namespace Engine {
	class Debug {
	public:
		template<typename T>
		constexpr static inline void Log(T& value) {
			std::cout << value << std::endl;
		};

		template<typename T, typename ...Ts>
		constexpr static inline void Log(T& value, Ts&& ...rest) {
			std::cout << value << "\t";
			Log(std::forward<Ts>(rest)...);
		};

		template<typename T>
		constexpr static inline void Error(T& value) {
			std::cout << value << std::endl;
		};

		template<typename T, typename ...Ts>
		constexpr static inline void Error(T& value, Ts&& ...rest) {
			std::cout << value << "\t";
			Log(std::forward<Ts>(rest)...);
		};
	};
}
