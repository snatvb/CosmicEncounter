#include "Anchor.h"
#include <cmath>

float degreesToRadians(float angle) {
	return static_cast<float>(angle * M_PI / 180);
}

using Point = Components::Transform::Position;

inline Point rotate(Point origin, Point point, float angle) {
	auto cosA = cos(angle);
	auto sinA = sin(angle);
	auto px = point.x;
	auto py = point.y;
	auto ox = origin.x;
	auto oy = origin.y;
	auto x = cosA * (px - ox) - sinA * (py - oy) + ox;
	auto y = sinA * (px - ox) + cosA * (py - oy) + oy;
	return Point{ x, y };
}

inline Point rotateZero(const Point& point, float angle) {
	auto cosA = cos(angle);
	auto sinA = sin(angle);
	auto x = point.x * cosA - point.y * sinA;
	auto y = point.y * cosA + point.x * sinA;
	return Point{ x, y };
}

Point getRelativeRotationPosition(const Components::Anchor& anchor, const Point& pos) {
	return Point{
		(pos.x + anchor.rotationCenter.x + anchor.offset.x),
		(pos.y + anchor.rotationCenter.y + anchor.offset.y)
	};
}


namespace Systems {
	void Anchor::run(ECS::FilteredEntities& entities)
	{
		for (auto& entity : entities) {
			auto& anchor = entity->getComponent<Components::Anchor>();

			if (auto targetEntity = _world->getEntityById(anchor.entityId)) {
				if (targetEntity->hasComponent<Components::Transform>()) {
					auto& target = targetEntity->getComponent<Components::Transform>();
					auto& transform = entity->getComponent<Components::Transform>();

					if (anchor.rotationCenter.x < 0 || anchor.rotationCenter.y < 0) {
						transform.position.x = target.position.x + anchor.jointCenter.x + anchor.offset.x;
						transform.position.y = target.position.y + anchor.jointCenter.y + anchor.offset.y;
					}
					else {
						auto radAngle = degreesToRadians(target.rotation);
						auto diff = Point{ static_cast<float>(anchor.jointCenter.x - anchor.rotationCenter.y), static_cast<float>(anchor.jointCenter.y - anchor.rotationCenter.y) };
						auto targetPos = rotateZero(diff, radAngle);
						auto position = getRelativeRotationPosition(anchor, targetPos);
						transform.position.x = target.position.x + position.x;
						transform.position.y = target.position.y + position.y;
					}
				}
			}
			else {
				entity->addComponent<Components::ToRemoveTag>();
			}
		}
	}
}
