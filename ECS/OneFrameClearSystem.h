#pragma once
#include "Component.h"
#include "Filter.h"
#include "System.h"

namespace ECS {
	class OneFrameClearSystem : public System<OneFrameClearSystem> {
	public:
		using Filter = Filters::OneFrame;

		void run(FilteredEntities& entities) {
			for (auto entity : entities) {
				entity->clearOneFrameComponents();
			}
		}
	};
}
