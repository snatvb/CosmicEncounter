#include "shot.h"
#include "../Builders.h"

void helpers::shotOnLine(ECS::World& world, float buffer, const std::pair<const ECS::Entity&, const ECS::Entity&>& followerTarget)
{
	auto [follower, target] = followerTarget;
	auto& targetTransform = target.getComponent<Components::Transform>();
	auto& transform = follower.getComponent<Components::Transform>();
	auto& gun = follower.getComponent<Components::Gun>();

	float diffX = transform.position.x + gun.offset.x - targetTransform.position.x;
	float halfBuffer = buffer / 2;
	if (diffX < halfBuffer && diffX > -halfBuffer) {
		if (gun.cooldown <= 0) {
			auto position = transform.position + gun.offset;
			Builders::CollideLayers igonreLayers{ CollideLayer::Enemy };
			Builders::createBulletByGun(world, follower.id, gun, position, igonreLayers);
			gun.cooldown = static_cast<int>(1000 / gun.fireRate);
		}
	}

	if (gun.cooldown > 0) {
		gun.cooldown -= static_cast<int>(Engine::Game::GetInstance().time.deltaMs());
	}
}
