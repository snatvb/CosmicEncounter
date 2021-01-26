#pragma once
#include "Entity.h"
#include "System.h"

namespace ECS {
	class BaseSystem;

	class World {
	public:
		void update() {
			std::vector<Entity*> filteredEntities;
			for (auto& system : _systems) {
				Filter& filter = system->getFilter();
				if (filter.type == Filter::Type::Nothing) {
					system->run(filteredEntities);
				}
				else {
					for (auto& entity : _entites) {
						if (filter.validate(*entity)) {
							filteredEntities.push_back(entity.get());
						}
					}
					system->run(filteredEntities);
					filteredEntities.clear();
				}
			}
		};

		Entity& newEntity() {
			auto entity = new Entity();
			std::unique_ptr<Entity> entityPtr{ entity };
			_entites.emplace_back(std::move(entityPtr));
			return *entity;
		}

		template<typename T>
		T& registerSystem() {
			T* system = new T();
			system->_world = this;
			system->init();
			std::unique_ptr<BaseSystem> systemPtr{ system };
			_systems.emplace_back(std::move(systemPtr));
			return *system;
		}

	private:
		std::vector<std::unique_ptr<Entity>> _entites;
		std::vector<std::unique_ptr<BaseSystem>> _systems;
	};
}
