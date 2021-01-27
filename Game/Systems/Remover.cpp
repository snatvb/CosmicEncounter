#include "Remover.h"

void Systems::Remover::run()
{
	for (auto entity : *filter.entities) {
		_world->removeEntity(*entity);
	}
}
