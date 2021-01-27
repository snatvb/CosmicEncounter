#pragma once

namespace ECS {
	class World;
	class Filter;
	class Entity;
	using FilteredEntities = std::vector<Entity*>;
	using FilterList = std::vector<Filter*>;

	class BaseSystem {
	public:
		bool isActive = true;
		FilterList filters;

		virtual Filter& getFilter() = 0;
		virtual void init() = 0;
		virtual void run(FilteredEntities& entities) {};
		virtual void run() {};

	protected:
		BaseSystem(SystemID id) : _id(id) {}
		SystemID _id;
		World* _world = nullptr;

		friend class World;
	};

	template<typename Impl>
	class System : public BaseSystem {
	public:
		System() : BaseSystem(getSystemTypeID<Impl>()) {}

		virtual void init() {};

		auto getFilter() {
			using Filter = typename Impl::Filter;
			static auto filter = Filter();
			return &filter;
		}
	};
}
