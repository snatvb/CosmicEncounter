#include "Stars.h"

void Builders::createStar(ECS::World& world, Vector2D<int>& offset, Components::Transform::Position& position, float speed) {
	auto texture = Engine::Game::GetInstance().assets->textures.load(AssetPathes::starts);

	auto tileSize = Size{ 8, 8 };
	auto& entity = world.newEntity();
	auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, offset, tileSize);
	gfx.layer = static_cast<char>(Engine::Layer::Background);
	entity.addComponent<Components::Transform>(position);
	entity.addComponent<Components::Star>(speed);
}
