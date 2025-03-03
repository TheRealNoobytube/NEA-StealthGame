#pragma once
#include "Source/Entities/Entity.h"


class Projectile : public Entity {
protected:
	void onDespawn();

public:
	Projectile(std::string name = "Projectile");

	Entity* owner = nullptr;

	float damage = 1;

	AnimatedSprite* sprite = new AnimatedSprite();
	CollisionRect* collision = new CollisionRect();

	TimerNode* despawnTimer = new TimerNode();

	void despawn();

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;

	void setDespawnTime(float time);

};