#pragma once

namespace ECS {
	class World;
	class Filter;
	class Entity;
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

		virtual void init() {};

		auto getFilter() {
			using Filter = typename Impl::Filter;
			static auto filter = Filter();
			return &filter;
		}
	};
}
