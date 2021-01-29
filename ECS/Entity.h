#pragma once
#include <functional>
#include "Common.h"
#include "Component.h"

namespace ECS {
	using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

	class Entity {
	public:
		enum class ChangeType {
			RemovedComponent,
			AddedComponent,
		};
		using OnChange = std::function<void(Entity&, Component&, ChangeType)>;

		EntityID id;

		Entity(OnChange onChange) : id(getEntityId()), _onChange(onChange) {}

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
			if (componentIs(*component, ComponentType::OneFrame)) {
				_oneFrameComponentCount++;
			}
			_onChange(*this, *component, ChangeType::AddedComponent);

			return *component;
		}

		template<typename T>
		void addComponent(T* component) {
			if (hasComponent<T>()) {
				// TODO: throw error in debug
				return;
			}

			auto id = getComponentTypeID<T>();

			_componentArray[id] = component;
			_componentBitSet[id] = true;
			if (componentIs(*component, ComponentType::OneFrame)) {
				_oneFrameComponentCount++;
			}
			_onChange(*this, *component, ChangeType::AddedComponent);
		}

		template<typename T>
		T& getComponent() const {
			auto component = _componentArray[getComponentTypeID<T>()];
			return *static_cast<T*>(component);
		}

		template<typename T>
		T* tryGetComponent() const {
			if (hasComponent<T>()) {
				auto component = _componentArray[getComponentTypeID<T>()];
				return static_cast<T*>(component);
			}
			return nullptr;
		}

		template<typename T>
		bool removeComponent() {
			if (hasComponent<T>()) {
				auto id = getComponentTypeID<T>();
				_removeComponentById(id);
				return true;
			}
			return false;
		}

		inline bool hasOneFrameComponents() {
			return _oneFrameComponentCount > 0;
		}

		inline void clearOneFrameComponents() {
			for (ComponentID i = 0; i < _componentArray.size(); i++)
			{
				if (_componentBitSet[i]) {
					auto component = _componentArray[i];
					if (componentIs(*component, ComponentType::OneFrame)) {
						_removeComponentById(i);
					}
				}
			}
		}

		inline bool hasComponents() {
			return _componentBitSet.any();
		}

	private:
		bool _active = true;
		unsigned char _oneFrameComponentCount = 0;
		ComponentArray _componentArray{};
		ComponentBitSet _componentBitSet;
		OnChange _onChange;

		inline void _removeComponentById(ComponentID id) {
			auto component = _componentArray[id];
			if (componentIs(*component, ComponentType::OneFrame)) {
				_oneFrameComponentCount--;
			}
			_onChange(*this, *component, ChangeType::RemovedComponent);
			_componentArray[id] = nullptr;
			_componentBitSet[id] = false;
			delete component;
		}
	};
}
