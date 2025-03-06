#include "Projectile.h"

Projectile::Projectile(std::string name) : Entity(name){
	addChild(collision);
	addChild(sprite);
	addChild(despawnTimer);
}

void Projectile::ready() {
	__super::ready();
	sprite->setTexture(getSceneTree()->getBasePath() + "../Assets/Projectiles/PistolShot.png");

	layer = PROJECTILES;
	mask = WORLD | ENTITIES;

	speed = 1;

	collision->position = Vector2D(1, 1);
	collision->setSize(Vector2D(5, 5));

	despawnTimer->setLength(1);
	despawnTimer->loop = false;
	despawnTimer->timeout.connect([this]() { despawn(); });
	despawnTimer->start();
}

void Projectile::update(float delta) {
	__super::update(delta);
}

void Projectile::physicsUpdate(float delta) {
	__super::physicsUpdate(delta);
	movement->velocity.x = speed * movement->direction.x;
	movement->velocity.y = speed * movement->direction.y;
	
	List<CollisionData> data = movement->applyVelocity();

	bool hasHit = false;

	for (int i = 0; i < data.getSize(); i++) {
		if (data.get(i).body != owner) {
			hasHit = true;

			if (data.get(i).body->layer == ENTITIES) {
				Entity* entity = reinterpret_cast<Entity*>(data.get(i).body);
				entity->health->dealDamage(damage);
			}
		}
	}

	if (hasHit) {
		despawn();
	}
}


void Projectile::despawn() {
	onDespawn();

	queueFree();
}

void Projectile::onDespawn() {}

void Projectile::setDespawnTime(float time) {
	despawnTimer->setLength(time);
}