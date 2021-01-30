#include "Bullets.h"

using namespace Components;

ECS::Entity& Builders::createDefaultBullet(ECS::World& world, Engine::Game& game, Gun& gun, Point& point, CollideLayers& ignoreLayers) {
	Size tileSize{ 9, 15 };
	auto& entity = world.newEntity();
	entity.addComponent<Transform>(point, tileSize);
	entity.addComponent<Bullet>(gun.direction, gun.bulletSpeed, gun.damage);

	auto& collider = entity.addComponent<CircleCollider>(4.0f, 5.0f, 3.0f);
	collider.layer = static_cast<size_t>(CollideLayer::Bullet);
	for (auto layer : ignoreLayers) {
		collider.layers[static_cast<size_t>(layer)] = false;
	}

	auto texture = game.assets->textures.load(AssetPathes::bullets);
	auto& gfx = entity.addComponent<GFXAnimtion>(*texture, tileSize);
	gfx.play = false;
	gfx.rotation = gun.direction.y > 0 ? 180.0f : 0.0f;

	return entity;
}

ECS::Entity& Builders::createGrenadeBullet(ECS::World& world, Engine::Game& game, Gun& gun, Point& point, CollideLayers& ignoreLayers) {
	Size tileSize{ 10, 26 };
	auto& entity = world.newEntity();
	entity.addComponent<Transform>(point, tileSize);
	entity.addComponent<Bullet>(gun.direction, gun.bulletSpeed, gun.damage);

	auto& collider = entity.addComponent<CircleCollider>(5.0f, 20.0f, 10.0f);
	collider.layer = static_cast<size_t>(CollideLayer::Bullet);
	for (auto layer : ignoreLayers) {
		collider.layers[static_cast<size_t>(layer)] = false;
	}

	Vector2D<int> frames{ 10, 6 };
	auto texture = game.assets->textures.load(AssetPathes::smallFireball10x26);
	auto& gfx = entity.addComponent<GFXAnimtion>(*texture, tileSize, frames);
	gfx.rotation = gun.direction.y > 0 ? 0.0f : 180.0f;

	return entity;
}

ECS::Entity* Builders::createBulletByGun(ECS::World& world, Engine::Game& game, Gun& gun, Point& point, CollideLayers& ignoreLayers) {
	switch (gun.type)
	{
	case Gun::Type::Default:
		return &Builders::createDefaultBullet(world, game, gun, point, ignoreLayers);
	case Gun::Type::Grenade:
		return &Builders::createGrenadeBullet(world, game, gun, point, ignoreLayers);
	default:
		return nullptr;
		break;
	}
}

ECS::Entity* Builders::createBulletByGun(ECS::World& world, Gun& gun, Point& point, CollideLayers& ignoreLayers) {
	auto& game = Engine::Game::GetInstance();
	return createBulletByGun(world, game, gun, point, ignoreLayers);
}
