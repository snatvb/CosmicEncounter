#include "Collide.h"

inline void handleCollide(ECS::Entity& entity1, ECS::Entity& entity2, ECS::World& world) {
	auto& collider1 = entity1.getComponent<Components::CircleCollider>();
	auto& collider2 = entity2.getComponent<Components::CircleCollider>();
	if (!collider1.layers[collider2.layer] || !collider2.layers[collider1.layer]) { return; }

	auto& transform1 = entity1.getComponent<Components::Transform>();
	auto& transform2 = entity2.getComponent<Components::Transform>();

	auto centerCollider1 = collider1.center + transform1.position;
	auto centerCollider2 = collider2.center + transform2.position;
	if (centerCollider1.dist(centerCollider2) <= collider1.radius + collider2.radius) {
		entity1.addComponent<Components::Collided>(entity2.id);
	}
}

void Systems::Collide::run()
{
	for (auto entity1 : *filter.entities) {
		if (!entity1->hasComponent<Components::Transform>()) {
			continue;
		}
		
		for (auto entity2 : *filter.entities) {
			if (!entity2->hasComponent<Components::Transform>() || entity1->id == entity2->id) {
				continue;
			}
			handleCollide(*entity1, *entity2, *_world);
		}
	}
}
