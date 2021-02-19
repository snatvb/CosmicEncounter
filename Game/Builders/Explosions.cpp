#include "Explosions.h"

void Builders::createSimpleExplosion(ECS::World& world, const Components::Transform::Position& position) {
	auto texture = Engine::Game::GetInstance().assets->textures.load(AssetPathes::simpleExplostion);

	auto tileSize = Size{ 32, 32 };
	auto& entity = world.newEntity();
	Vector2D<int> frames{ 5, 1 };
	auto& gfx = entity.addComponent<Components::GFXAnimtion>(*texture, tileSize, frames);
	gfx.layer = static_cast<char>(Engine::Layer::Effects);
	gfx.speed = 0.5f;
	entity.addComponent<Components::Transform>(position);
	entity.addComponent<Components::GFXDestroyByEndAnimationTag>();
}
