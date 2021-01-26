#pragma once

#include "ECS.h"
#include "Engine.h"
#include "../Components/Components.h"

namespace Systems {
	class ControlPlayer : public ECS::System<ControlPlayer> {
	public:
		using Filter = ECS::Filters::Include<Components::PlayerTag>;

		void init() override;
		void run(ECS::FilteredEntities& enitites) override;
	private:
		Engine::Game* _game;
	};
}
