#pragma once
#include "Source/Entities/Entity.h"
#include "Source/Entities/Player/Player.h"

class Pathfinding;

class Enemy : public Entity {
public:
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

	Raycast* detectCast = new Raycast();

	Pathfinding* pathfinding;
	Player* player;

	TimerNode* pathTimer = new TimerNode();

	AnimatedSprite* sprite = new AnimatedSprite();
	CollisionRect* collision = new CollisionRect();

	bool disableAI = true;

	bool walking = false;

	Enemy(std::string name = "Enemy");

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;

	void onPathTimerTimeout();

	void onDeath(float damage) override;
};

#include "Source/Pathfinding/Pathfinding.h"
