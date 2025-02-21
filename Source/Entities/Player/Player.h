#pragma once
#include "Source/Entities/Entity.h"
#include "Source/Nodes/Camera/Camera.h"

class Player : public Entity {
private:
	
	enum State {
		IDLE,
		MOVING,
		LEAN
	};

	State currentState;
	State nextState = IDLE;


	enum HorizontalDirection {
		LEFT,
		RIGHT,
		H_NONE
	};

	enum VerticalDirection {
		UP,
		DOWN,
		V_NONE
	};

	VerticalDirection vertical = UP;
	HorizontalDirection horizontal = H_NONE;

	bool isColliding = false;

	Camera camera;
	AnimatedSprite sprite;
	CollisionRect collisionRect;

	float defaultCameraSpeed = 8;
	float leanCameraSpeed = 3;

	int cameraLeanOffsetAmount = 50;
	int cameraLeanRaycastLength = 16;
	Raycast cameraLeanRaycast;
	TimerNode cameraLeanTimer;

	void cameraLeanTimerTimeout();

	void stateEntered(State state);
	void stateExited(State state);
	void stateUpdate(State state);
	void calculateMovement();

public:
	Player(std::string name = "Player");

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;
};

