#pragma once
#include "Entity.h"
#include "Filter.h"
#include "World.h"

namespace ECS {
	class World;
	using FilteredEntities = std::vector<Entity*>;

	class BaseSystem {
	public:
		bool isActive = true;

		virtual Filter& getFilter() = 0;
		virtual void init() = 0;
		virtual void run(FilteredEntities& entities) = 0;

	protected:
		World* _world;

		friend class World;
	};

	template<typename Impl>
	class System : public BaseSystem {
	public:
		bool isActive = true;

		auto getFilter() {
			using Filter = typename Impl::Filter;
			static auto filter = Filter();
			return &filter;
		}
	};
}
