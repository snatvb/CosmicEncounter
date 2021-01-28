#include "CheckDied.h"

void Systems::CheckDied::run()
{
	for (auto entity : *filter.entities) {
		auto& stats = entity->getComponent<Components::HeroStats>();
		if (stats.health <= 0) {
			entity->addComponent<Components::ToRemoveTag>();
		}
	}
}
