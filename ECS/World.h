#pragma once
#include <vector>
#include <algorithm>
#include <map>
#include "System.h"
#include "Filter.h"

namespace ECS {
	class BaseSystem;
	class Entity;
	class Filter;

	class World {
	public:
		using Entities = std::vector<Entity*>;
		using Systems = std::vector<BaseSystem*>;

		World() {
			_entities.reserve(256);
		}

		void init() {
			for (auto& system : _systems) {
				Filter& filter = system->getFilter();
				_filteredEntities[&filter] = std::vector<Entity*>{};
			}
		}

		inline void filterEntities(Entities& entityPool, Filter& filter) {
			for (auto& entity : _entities) {
				if (filter.validate(*entity)) {
					entityPool.emplace_back(entity);
				}
			}
		}

		inline Entities filterEntities(Filter& filter) {
			Entities entityPool;
			for (auto& entity : _entities) {
				if (filter.validate(*entity)) {
					entityPool.emplace_back(entity);
				}
			}
			return entityPool;
		}

		void update() {
			std::vector<Entity*> filteredEntities;
			for (auto& system : _systems) {
				Filter& filter = system->getFilter();
				if (filter.type == Filter::Type::Nothing) {
					system->run(filteredEntities);
				}
				else {
					filterEntities(filteredEntities, filter);
					system->run(filteredEntities);
					filteredEntities.clear();
				}
			}

			for (auto entity : _entities) {
				entity->clearOneFrameComponents();
			}
		};

		Entity& newEntity() {
			auto entity = new Entity(*this);
			_entities.emplace_back(entity);
			return *entity;
		}

		Entity* getEntityById(EntityID id) {
			for (auto& entity : _entities) {
				if (entity->id == id) {
					return entity;
				}
			}

			return nullptr;
		}

		inline void removeEntity(EntityID id) {
			_entities.erase(std::remove_if(
				_entities.begin(),
				_entities.end(),
				[&](Entity* item) { return id == item->id; }
			), _entities.end());

			for (auto [_, entities] : _filteredEntities) {
				entities.erase(std::remove_if(
					entities.begin(),
					entities.end(),
					[&](Entity* item) { return id == item->id; }
				), entities.end());
			}
		}

		inline void removeEntity(Entity& entity) {
			removeEntity(entity.id);
		}

		template<typename T>
		T& registerSystem() {
			T* system = new T();
			system->_world = this;
			auto filter = system->getFilter();
			system->init();
			_systems.emplace_back(system);
			return *system;
		}

	private:
		std::map<Filter*, Entities> _filteredEntities;
		Entities _entities;
		Systems _systems;

		void _componentAdded(Entity& entity) {
			for (auto [filter, entities] : _filteredEntities) {
				if (filter->validate(entity)) {
					entities.emplace_back(&entity);
				}
			}
		}

		void _componentRemoved(Entity& entity) {
			for (auto [filter, entities] : _filteredEntities) {
				if (!filter->validate(entity)) {
					entities.erase(std::remove_if(
						entities.begin(),
						entities.end(),
						[&](Entity* item) { return entity.id == item->id; }
					), entities.end());
				}
			}
		}

		friend class Entity;
	};
}
