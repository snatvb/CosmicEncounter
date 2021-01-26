#pragma once
#include <map>
#include <functional>
#include "ECS.h"
#include "Common.h"

namespace Engine {
	class Worker {
	public:
		virtual void inline init() = 0;
		virtual void inline update() = 0;
		virtual ECS::World& getWorld();

	protected:
		RenderCache _renderCache;
	private:
		ECS::World _world;
	};
}
