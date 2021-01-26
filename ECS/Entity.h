#pragma once
#include "Common.h"
#include "Component.h"

namespace ECS {
	using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

	class Entity {
	public:
		bool isActive() { return _active;  };

		template<typename T>
		bool hasComponent() const {
			return _componentBitSet[getComponentTypeID<T>()];
		};

		template<typename T, typename ...TArgs>
		T& addComponent(TArgs&& ...args) {
			T* component = new T(std::forward<TArgs>(args)...);
			std::unique_ptr<Component> componentPtr{ component };
			_components.emplace_back(std::move(componentPtr));

			_componentArray[getComponentTypeID<T>()] = component;
			_componentBitSet[getComponentTypeID<T>()] = true;

			return *component;
		}

		template<typename T>
		T& getComponent() const {
			auto component = _componentArray[getComponentTypeID<T>()];
			return *static_cast<T*>(component);
		}

	private:
		bool _active;
		std::vector<std::unique_ptr<Component>> _components;
		ComponentArray _componentArray;
		ComponentBitSet _componentBitSet;
	};
}
