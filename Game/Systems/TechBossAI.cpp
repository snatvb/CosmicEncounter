#include "TechBossAI.h"

using namespace Components;

void Systems::TechBossAI::init()
{
}

// TODO: MOVE TO HELPERS
inline void shot(ECS::World& world, Engine::Game& game, const ECS::Entity& player, const ECS::Entity& entity) {
	auto& playerTransform = player.getComponent<Components::Transform>();
	auto& transform = entity.getComponent<Components::Transform>();
	auto& gun = entity.getComponent<Components::Gun>();

	float diffX = transform.position.x - playerTransform.position.x;
	if (diffX < 2.0f && diffX > -2.0f) {
		if (gun.cooldown <= 0) {
			auto position = transform.position + gun.offset;
			Builders::CollideLayers igonreLayers{ CollideLayer::Enemy };
			Builders::createBulletByGun(world, entity.id, gun, position, igonreLayers);
			Engine::Debug::Log("TechBoss shot!");
			gun.cooldown = static_cast<int>(1000 / gun.fireRate);
		}
	}

	if (gun.cooldown > 0) {
		gun.cooldown -= static_cast<int>(game.time.deltaMs());
	}
}

void Systems::TechBossAI::run()
{
	auto* boss = filter.entities->front();
	auto* player = playerFilter.entities->front();
	const auto deltaTime = Engine::Game::GetInstance().time.delta();

	const auto& playerTransform = player->getComponent<Transform>();
	auto& transform = boss->getComponent<Transform>();
	const auto& bossStats = boss->getComponent<HeroStats>();
	auto& techBoss = boss->getComponent<TechBoss>();
	// TODO: move to helpers - following position
	auto diffX = transform.position.x + 32 - playerTransform.position.x;
	if (diffX > 16.0f) {
		transform.position.x -= static_cast<int>(bossStats.speed * deltaTime);
	} else if (diffX < -16.0f) {
		transform.position.x += static_cast<int>(bossStats.speed * deltaTime);
	}
	shot(*_world, Engine::Game::GetInstance(), *player, *boss);
}
