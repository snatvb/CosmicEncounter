#include "EnemySpawner.h"

void Systems::EnemySpawner::run(ECS::FilteredEntities& entities)
{
	if (entities.size() >= 3) {
		return;
	}

}
