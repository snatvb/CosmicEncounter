#include "Remover.h"

void Systems::Remover::run(ECS::FilteredEntities& entities)
{
	for (auto entity : entities) {
		_world->removeEntity(*entity);
	}
}
