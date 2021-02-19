#include "Bullets.h"

using namespace Components;

ECS::Entity& Builders::createDefaultBullet(ECS::World& world, ECS::EntityID ownerId, Gun& gun, Point& point, CollideLayers& ignoreLayers) {
	auto& game = Engine::Game::GetInstance();
	Size tileSize{ 9, 15 };
	auto& entity = world.newEntity();
	entity.addComponent<Transform>(point, tileSize);
	auto& bullet = entity.addComponent<Bullet>(ownerId, gun.direction, gun.bulletSpeed, gun.damage);
	bullet.ignoreEntities.push_back(ECS::getComponentTypeID<Components::TechBoss>());

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

ECS::Entity& Builders::createGrenadeBullet(ECS::World& world, ECS::EntityID ownerId, Gun& gun, Point& point, CollideLayers& ignoreLayers) {
	auto& game = Engine::Game::GetInstance();
	Size tileSize{ 9, 25 };
	auto& entity = world.newEntity();
	entity.addComponent<Transform>(point, tileSize);
	entity.addComponent<Bullet>(ownerId, gun.direction, gun.bulletSpeed, gun.damage);

	auto& collider = entity.addComponent<CircleCollider>(5.0f, 20.0f, 10.0f);
	collider.layer = static_cast<size_t>(CollideLayer::Bullet);
	for (auto layer : ignoreLayers) {
		collider.layers[static_cast<size_t>(layer)] = false;
	}

	Vector2D<int> frames{ 10, 6 };
	auto texture = game.assets->textures.load(AssetPathes::smallGreenFireball9x25);
	auto& gfx = entity.addComponent<GFXAnimtion>(*texture, tileSize, frames);
	gfx.rotation = gun.direction.y > 0 ? 0.0f : 180.0f;

	return entity;
}

ECS::Entity& Builders::createFoilBullet(ECS::World& world, ECS::EntityID ownerId, const Gun& gun, const Point& point, const CollideLayers& ignoreLayers) {
	auto& game = Engine::Game::GetInstance();
	Size tileSize{ 64, 16 };
	auto& entity = world.newEntity();
	entity.addComponent<Transform>(point, tileSize);
	entity.addComponent<Bullet>(ownerId, gun.direction, gun.bulletSpeed, gun.damage);

	auto& collider = entity.addComponent<CircleCollider>(32.0f, 8.0f, 12.0f);
	collider.layer = static_cast<size_t>(CollideLayer::Bullet);
	for (auto layer : ignoreLayers) {
		collider.layers[static_cast<size_t>(layer)] = false;
	}

	Vector2D<int> frames{ 5, 1 };
	auto texture = game.assets->textures.load(AssetPathes::fiolBullet);
	auto& gfx = entity.addComponent<GFXAnimtion>(*texture, tileSize, frames);
	gfx.speed = 0.3f;
	gfx.loop = false;
	gfx.rotation = gun.direction.y > 0 ? 90.0f : -90.0f;

	return entity;
}

ECS::Entity* Builders::createBulletByGun(
	ECS::World& world,
	ECS::EntityID ownerId,
	Gun& gun,
	Point& point,
	CollideLayers& ignoreLayers
) {
	switch (gun.type)
	{
	case Gun::Type::Default:
		return &Builders::createDefaultBullet(world, ownerId, gun, point, ignoreLayers);
	case Gun::Type::Grenade:
		return &Builders::createGrenadeBullet(world, ownerId, gun, point, ignoreLayers);
	case Gun::Type::Fiol:
		return &Builders::createFoilBullet(world, ownerId, gun, point, ignoreLayers);
	default:
		return nullptr;
		break;
	}
}
