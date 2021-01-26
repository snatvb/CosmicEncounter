#include "Anchor.h"

namespace Systems {
	void Anchor::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& anchor = entity->getComponent<Components::Anchor>();

			if (auto targetEntity = _world->getEntityById(anchor.entityId)) {
				if (targetEntity->hasComponent<Components::Position>()) {
					auto& targetPosition = targetEntity->getComponent<Components::Position>();
					auto& position = entity->getComponent<Components::Position>();

					position.x = targetPosition.x + anchor.offset.x;
					position.y = targetPosition.y + anchor.offset.y;
				}
			}
			else {
				entity->addComponent<Components::ToRemoveTag>();
			}
		}
	}
}
