#pragma once
#include "Source/Nodes/AnimatedSprite/AnimatedSprite.h"
#include "Source/Collision/CollisionBody.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/Components/Movement/MovementComponent.h"

class Player : public CollisionBody {
private:
	AnimatedSprite sprite;
	CollisionRect collisionRect;
	MovementComponent movement;

	int animationTimer = 0;
	int fps = 12;
	int walkingFrame = 1;

	float speed = 1;

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

public:
	Player(std::string name = "Player");

	//direction is a unit vector, meaning its magnitude will always be 1 or -1

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;

};

