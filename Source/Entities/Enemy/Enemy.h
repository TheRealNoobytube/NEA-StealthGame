#pragma once
#include "Source/Entities/Entity.h"

class Enemy : public Entity {
public:
	AnimatedSprite sprite;
	MovementComponent movement = MovementComponent(this);
	CollisionRect collision;

	enum WalkingDirection {
		WALKING_RIGHT,
		WALKING_UP_RIGHT,
		WALKING_UP,
		WALKING_UP_LEFT,
		WALKING_LEFT,
		WALKING_DOWN_LEFT,
		WALKING_DOWN,
		WALKING_DOWN_RIGHT
	};

	WalkingDirection walkDirection = WALKING_UP;

	float speed = 1;
	bool walking = false;

	Enemy(std::string name = "Enemy");

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;
};