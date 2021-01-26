#pragma once
#include "Entity.h"
#include <iostream>

namespace ECS {
	class Entity;

	template<typename ...Args> struct FilterHelper;

	template<>
	struct FilterHelper<> {
		static bool hasComponent(ECS::Entity& entity)
		{
			return false;
		}

		static bool hasComponents(ECS::Entity& entity)
		{
			return true;
		}
	};

	template<typename A, typename ...Args>
	struct FilterHelper<A, Args...> {
		static bool hasComponent(ECS::Entity& entity)
		{
			if (entity.hasComponent<A>()) {
				return true;
			}

			return FilterHelper<Args...>::hasComponent(entity);
		}

		static bool hasComponents(ECS::Entity& entity)
		{
			if (!entity.hasComponent<A>()) {
				return false;
			}

			return FilterHelper<Args...>::hasComponents(entity);
		}
	};

	class Filter {
	public:
		enum class Type {
			Include,
			Exclude,
			With,
			All,
			None,
			Nothing,
			OneFrame,
		};

		Type type = Type::None;
		Filter()
			: _id(getFilterId()) {
			std::cout << "Filter created" << std::endl;
		}

		FilterID getId() { return _id; };
		virtual bool validate(ECS::Entity& entity) = 0;
	protected:
	private:
		FilterID _id;
	};

	namespace Filters {
		template <typename ...ComponentTypes>
		class Include : Filter {
		public:
			Type type = Type::Include;

			bool validate(Entity& entity) {
				return FilterHelper<ComponentTypes...>::hasComponent(entity);
			};
		};

		template <typename ...ComponentTypes>
		class Exclude : Filter {
		public:
			Type type = Type::Exclude;

			bool validate(Entity& entity) {
				return !FilterHelper<ComponentTypes...>::hasComponent(entity);
			};
		};

		template <typename ...ComponentTypes>
		class With : Filter {
		public:
			Type type = Type::With;

			bool validate(Entity& entity) {
				return FilterHelper<ComponentTypes...>::hasComponents(entity);
			};
		};

		class All : Filter {
		public:
			Type type = Type::All;

			bool validate(Entity& entity) {
				return true;
			};
		};

		class Nothing : Filter {
		public:
			Type type = Type::Nothing;

			bool validate(Entity& entity) {
				return false;
			};
		};

		class OneFrame : Filter {
		public:
			Type type = Type::OneFrame;

			bool validate(Entity& entity) {
				return entity.hasOneFrameComponents();
			};
		};
	}
}
