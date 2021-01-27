#include "Filter.h"
namespace ECS {
	std::map<FilterID, FilteredEntities> Filter::_filters{};

	void Filter::handleRemovedEntity(ECS::Entity& entity) {
		entities->erase(std::remove(
			entities->begin(),
			entities->end(),
			&entity
		), entities->end());
	}
	void Filter::handleAddedComponent(ECS::Entity& entity) {
		if (validate(entity)) {
			if (std::find(entities->begin(), entities->end(), &entity) == entities->end()) {
				entities->emplace_back(&entity);
			}
		}
	}
	void Filter::handleRemovedComponent(ECS::Entity& entity) {
		if (!validate(entity)) {
			entities->erase(std::remove(
				entities->begin(),
				entities->end(),
				&entity
			), entities->end());
		}
	}
}