#include "TechBossAI.h"

using namespace Components;

void Systems::TechBossAI::init()
{
}

void Systems::TechBossAI::run()
{
	auto* boss = filter.entities->front();
	auto* player = playerFilter.entities->front();
	const auto deltaTime = Engine::Game::GetInstance().time.delta();

	const auto& playerTransform = player->getComponent<Transform>();
	auto& transform = boss->getComponent<Transform>();
	const auto& bossStats = boss->getComponent<HeroStats>();
	// TODO: move to helpers - following position
	auto diffX = transform.position.x + 32 - playerTransform.position.x;
	Engine::Debug::Log(diffX);
	if (diffX > 32.0f) {
		transform.position.x -= static_cast<int>(bossStats.speed * deltaTime);
	} else if (diffX < -32.0f) {
		transform.position.x += static_cast<int>(bossStats.speed * deltaTime);
	}
}
