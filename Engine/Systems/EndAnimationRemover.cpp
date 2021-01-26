#include "EndAnimationRemover.h"

void Systems::EndAnimationRemover::run(ECS::FilteredEntities& entities)
{
	for (auto entity : entities) {
		auto& gfx = entity->getComponent<Components::GFXAnimtion>();
		if (gfx.currentFrame == gfx.frames) {
			_world->removeEntity(entity->id);
		}
	}
}
