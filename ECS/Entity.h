#pragma once
#include "Common.h"
#include "Component.h"

namespace ECS {
	class World;
	using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

	class Entity {
	public:
		EntityID id;

		Entity() : id(getEntityId()) {}

		~Entity() {
			for (auto component : _componentArray) {
				delete component;
			}
		}

		bool isActive() { return _active; };

		template<typename T>
		bool hasComponent() const {
			return _componentBitSet[getComponentTypeID<T>()];
		};

		template<typename T, typename ...TArgs>
		T& addComponent(TArgs&& ...args) {
			if (hasComponent<T>()) {
				return getComponent<T>();
			}

			T* component = new T(std::forward<TArgs>(args)...);
			auto id = getComponentTypeID<T>();

			_componentArray[id] = component;
			_componentBitSet[id] = true;

			return *component;
		}

		template<typename T>
		T& getComponent() const {
			auto component = _componentArray[getComponentTypeID<T>()];
			return *static_cast<T*>(component);
		}

		template<typename T>
		bool removeComponent() {
			if (hasComponent<T>()) {
				auto id = getComponentTypeID<T>();
				auto component = _componentArray[id];
				_componentArray[id] = nullptr;
				_componentBitSet[id] = false;
				delete component;
				return true;
			}
			return false;
		}

		void clearOneFrameComponents() {
			for (ComponentID i = 0; i < _componentArray.size(); i++)
			{
				if (_componentBitSet[i]) {
					auto component = _componentArray[i];
					if (component->_getType() == Component::Type::OneFrame) {
						_componentArray[i] = nullptr;
						_componentBitSet[i] = false;
						delete component;
					}
				}
			}
		}

	private:
		bool _active = true;
		ComponentArray _componentArray{};
		ComponentBitSet _componentBitSet;

		friend class World;
	};
}
