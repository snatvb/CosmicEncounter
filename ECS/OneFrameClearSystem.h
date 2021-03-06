#pragma once
#include "Component.h"
#include "Filter.h"
#include "System.h"

namespace ECS {
	class OneFrameClearSystem : public System<OneFrameClearSystem> {
	public:
		Filters::OneFrame filter;
		REG_FILTERS(OneFrameClearSystem, &filter)

		void run() {
			for (auto entity : *filter.entities) {
				entity->clearOneFrameComponents();
			}
		}
	};
}
