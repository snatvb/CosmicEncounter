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
		BaseSystem(SystemID id) : _id(id) {}
		SystemID _id;
		World* _world;

		friend class World;
	};

	template<typename Impl>
	class System : public BaseSystem {
	public:
		bool isActive = true;

		System() : BaseSystem(getSystemTypeID<Impl>()) {}

		virtual void init() {};

		auto getFilter() {
			using Filter = typename Impl::Filter;
			static auto filter = Filter();
			return &filter;
		}
	};
}
