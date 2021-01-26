#pragma once
#include <vector>
#include <memory>
#include <bitset>
#include <array>

namespace ECS {
	constexpr std::size_t MAX_COMPONENTS = 32;

	using ComponentID = std::size_t;
	using ComponentBitSet = std::bitset<MAX_COMPONENTS>;

	inline ComponentID getComponentTypeID() {
		static ComponentID lastID = 0;
		return lastID++;
	}

	template<typename T>
	inline ComponentID getComponentTypeID() noexcept {
		static ComponentID typeID = getComponentTypeID();
		return typeID;
	}
}
