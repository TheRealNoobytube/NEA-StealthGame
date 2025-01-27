#pragma once
#include "Source/Entities/Entity.h"
#include "Source/Pathfinding/Pathfinding.h"
#include "Source/Entities/Player/Player.h"

class Enemy : public Entity {
public:
	Pathfinding pathfinding;

	TimerNode pathTimer;

	void onPathTimerTimeout();


	Player* player;

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

	bool walking = false;

	Enemy(std::string name = "Enemy");

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;
};