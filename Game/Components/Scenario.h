#pragma once
#include <array>
#include "Utils/EnumArray.h"
#include "ECS.h"
#include "./Enemy.h"

namespace Components {
	struct Scenario : ECS::Component {
		enum class Boss {
			TechnicalPlanet
		};

		using EnemyType = Enemy::Type;

		using EnemiesCount = EnumArray<EnemyType, unsigned char, static_cast<size_t>(EnemyType::__count)>;

		EnemiesCount maxEnemies;
		EnemiesCount kills;
		EnemiesCount needKillsToBoss;
		Boss boss = Boss::TechnicalPlanet;
		bool finished = false;
	};
}
