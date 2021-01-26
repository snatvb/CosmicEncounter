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
				_filteredEntities[&filter] = Entities{};
			}
		}


		inline Entities filterEntities(Filter& filter) {
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
			}
		};

		Entity& newEntity() {
			auto entity = new Entity([this](Entity& entity, Component& component, Entity::ChangeType changeType) {
				_handleEntityChange(entity, component, changeType);
				});
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
			std::cout << "remove: " << id << std::endl;
			auto toDelete = std::find_if(_entities.begin(), _entities.end(), [&](Entity* item) { return id == item->id; });
			if (toDelete != _entities.end()) {
				for (auto& [_, entities] : _filteredEntities) {
					entities.erase(std::remove_if(
						entities.begin(),
						entities.end(),
						[&](Entity* item) { return item->id == id; }
					), entities.end());
				}
				Entity* x = *toDelete;
				_entities.erase(toDelete);
				delete x;
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

		void _handleEntityChange(Entity& entity, Component& component, Entity::ChangeType changeType) {
			switch (changeType)
			{
			case ECS::Entity::ChangeType::RemovedComponent:
				_handleComponentRemoved(entity);
				break;
			case ECS::Entity::ChangeType::AddedComponent:
				_handleComponentAdded(entity);
				break;
			default:
				break;
			}
		}

		void _handleComponentAdded(Entity& entity) {
			for (auto& [filter, entities] : _filteredEntities) {
				if (filter->validate(entity)) {
					entities.emplace_back(&entity);
				}
			}
		}

		void _handleComponentRemoved(Entity& entity) {
			for (auto& [filter, entities] : _filteredEntities) {
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
