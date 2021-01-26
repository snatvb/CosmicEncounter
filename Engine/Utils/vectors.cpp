#include "ECS.h"
#include <vector>

inline ECS::Entity* head(const std::vector<ECS::Entity*>& entities) {
	if (entities.begin() != entities.end()) {
		return *entities.begin();
	}
	return nullptr;
}
