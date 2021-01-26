#include "Anchor.h"
#include <cmath>

//float degreesToRadians(float angle) {
//	return angle * M_PI / 180;
//}

void rotate(Components::Anchor& anchor, Components::Transform& targetTransform, Components::Transform& transform) {
	auto targetX = targetTransform.position.x + anchor.center.x;
	auto targetY = targetTransform.position.y + anchor.center.y;
	transform.position.x = (int)(targetX + ((double)transform.position.x - targetX) * cos(transform.rotation) - ((double)transform.position.y - transform.position.y) * sin(targetTransform.rotation));
	transform.position.y = (int)(targetY + ((double)transform.position.y - targetY) * cos(targetTransform.rotation) + ((double)transform.position.x - targetX) * sin(targetTransform.rotation));
}

namespace Systems {
	void Anchor::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& anchor = entity->getComponent<Components::Anchor>();

			if (auto targetEntity = _world->getEntityById(anchor.entityId)) {
				if (targetEntity->hasComponent<Components::Transform>()) {
					auto& targetTransform = targetEntity->getComponent<Components::Transform>();
					auto& transform = entity->getComponent<Components::Transform>();

					transform.position.x = targetTransform.position.x + anchor.offset.x;
					transform.position.y = targetTransform.position.y + anchor.offset.y;
					transform.rotation = targetTransform.rotation;
					rotate(anchor, targetTransform, transform);
				}
			}
			else {
				entity->addComponent<Components::ToRemoveTag>();
			}
		}
	}
}
