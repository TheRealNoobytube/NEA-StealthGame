#pragma once
#include "Source/Nodes/Sprite/Sprite.h"
#include "Source/Nodes/AnimationPlayer/AnimationPlayer.h"

class Player : public Node2D {
private:
	Sprite sprite;
	AnimationPlayer animations;

	int animationTimer = 0;
	int fps = 12;
	int walkingFrame = 1;

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
	Vector2D direction = Vector2D(0, 0);
	Vector2D velocity = Vector2D(0, 0);
	float speed = 1;

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;

};

