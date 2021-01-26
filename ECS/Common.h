#pragma once
#include <vector>
#include <memory>
#include <bitset>
#include <array>

namespace ECS {
	constexpr std::size_t MAX_COMPONENTS = 64;

	using ComponentID = unsigned __int16;
	using EntityID = unsigned __int16;
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

	inline EntityID getEntityId() {
		static EntityID lastId = 0;
		return lastId++;
	}

	using FilterID = unsigned __int16;

	inline FilterID getFilterId() {
		static FilterID lastId = 0;
		return lastId++;
	}
}
