#pragma once
#include <vector>
#include <algorithm>
#include <map>
#include "System.h"
#include "Filter.h"
#include "OneFrameClearSystem.h"

namespace ECS {
	class BaseSystem;
	class Entity;
	class Filter;

	class World {
	public:
		using Entities = std::vector<Entity*>;
		using Systems = std::vector<BaseSystem*>;

		World() {
			registerSystem<OneFrameClearSystem>();
		}

		void init() {
			for (auto& system : _systems) {
				Filter& filter = system->getFilter();
				_filteredEntities[&filter] = Entities{};
			}
		}


		inline Entities& filterEntities(Filter& filter) {
			return _filteredEntities[&filter];
		}

		inline void update() {
			for (auto& system : _systems) {
				Filter& filter = system->getFilter();
				if (filter.type == Filter::Type::Nothing) {
					std::vector<Entity*> filteredEntities;
					system->run(filteredEntities);
				}
				else {
					auto entities = _filteredEntities[&filter];
					system->run(entities);
				}
				system->run();
			}
		};

		Entity& newEntity() {
			auto entity = new Entity([this](Entity& entity, Component& component, Entity::ChangeType changeType) {
				_handleEntityChange(entity, component, changeType);
				});
			_entities[entity->id] = entity;
			return *entity;
		}

		Entity* getEntityById(EntityID id) {
			auto found = _entities.find(id);
			if (found != _entities.end()) {
				auto [_, entity] = *found;
				return entity;
			}
			return nullptr;
		}

		inline void removeEntity(EntityID id) {
			std::cout << "remove: " << id << std::endl;
			auto toDelete = _entities.find(id);
			if (toDelete != _entities.end()) {
				auto [_, entity] = *toDelete;
				for (auto system : _systems) {
					for (auto filter : system->filters) {
						filter->handleRemovedEntity(*entity);
					}
				}
				for (auto& [_, entities] : _filteredEntities) {
					entities.erase(std::remove(
						entities.begin(),
						entities.end(),
						entity
					), entities.end());
				}
				_entities.erase(toDelete);
				delete entity;
			}
		}

		inline void removeEntity(Entity& entity) {
			removeEntity(entity.id);
		}

		template<typename T, typename ...TArgs>
		T& registerSystem(TArgs&& ...args) {
			T* system = new T(std::forward<TArgs>(args)...);
			system->_world = this;
			auto filter = system->getFilter();
			system->init();
			_systems.emplace_back(system);
			return *system;
		}

		template<typename T>
		Filter* getSystemFilter() {
			SystemID needID = getSystemTypeID<T>();
			for (auto system : _systems) {
				if (needID == system->_id) {
					auto& filter = system->getFilter();
					return &filter;
				}
			}
			return nullptr;
		}

	private:
		std::map<Filter*, Entities> _filteredEntities;
		std::map<EntityID, Entity*> _entities;
		Systems _systems;

		void _handleEntityChange(Entity& entity, Component& component, Entity::ChangeType changeType) {
			switch (changeType)
			{
			case ECS::Entity::ChangeType::RemovedComponent:
				_handleComponentRemoved(entity, component);
				break;
			case ECS::Entity::ChangeType::AddedComponent:
				_handleComponentAdded(entity, component);
				break;
			default:
				break;
			}
		}

		void _handleComponentAdded(Entity& entity, Component& component) {
			for (auto& [filter, entities] : _filteredEntities) {
				if (filter->validate(entity)) {
					if (std::find(entities.begin(), entities.end(), &entity) == entities.end()) {
						entities.emplace_back(&entity);
					}
				}
			}

			for (auto system : _systems) {
				for (auto filter : system->filters) {
					filter->handleAddedComponent(entity);
				}
			}
		}

		void _handleComponentRemoved(Entity& entity, Component& component) {
			for (auto& [filter, entities] : _filteredEntities) {
				if (!filter->validate(entity)) {
					entities.erase(std::remove_if(
						entities.begin(),
						entities.end(),
						[&](Entity* item) { return entity.id == item->id; }
					), entities.end());
				}
			}

			for (auto system : _systems) {
				for (auto filter : system->filters) {
					filter->handleRemovedComponent(entity);
				}
			}
		}

		friend class Entity;
	};
}
