#pragma once
#include <algorithm>
#include "Entity.h"
#include "System.h"

namespace ECS {
	class BaseSystem;

	class World {
	public:
		using Entities = std::vector<Entity*>;
		using Systems = std::vector<BaseSystem*>;

		World() {
			_entities.reserve(256);
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
			auto entity = new Entity();
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

		void removeEntity(Entity& entity) {
			_entities.erase(std::remove_if(
				_entities.begin(),
				_entities.end(),
				[&](Entity* item) { return &entity == item; }
			), _entities.end());
		}

		template<typename T>
		T& registerSystem() {
			T* system = new T();
			system->_world = this;
			system->init();
			_systems.emplace_back(system);
			return *system;
		}

	private:
		Entities _entities;
		Systems _systems;
	};
}
