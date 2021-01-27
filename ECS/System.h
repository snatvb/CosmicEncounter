#pragma once

#define REG_FILTERS(CLASSNAME, ...) \
    CLASSNAME() {\
		filters = ECS::FilterList{ ##__VA_ARGS__ };\
    }

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

		virtual void init() = 0;
		virtual void run() = 0;

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
	};
}
