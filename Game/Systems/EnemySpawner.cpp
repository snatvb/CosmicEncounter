#include "EnemySpawner.h"

void Systems::EnemySpawner::run()
{
	if (filter.entities->size() >= 3) {
		return;
	}

}
