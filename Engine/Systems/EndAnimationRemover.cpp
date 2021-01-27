#include "EndAnimationRemover.h"

void Systems::EndAnimationRemover::run()
{
	for (auto entity : *filter.entities) {
		auto& gfx = entity->getComponent<Components::GFXAnimtion>();
		if (gfx.currentFrame == gfx.frames) {
			_world->removeEntity(entity->id);
		}
	}
}
