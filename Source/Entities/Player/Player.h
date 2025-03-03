#pragma once
#include "Source/Entities/Entity.h"
#include "Source/Nodes/Camera/Camera.h"
#include "Source/Scenes/Levels/Level.h"

class Player : public Entity {
private:
	
	enum State {
		IDLE,
		MOVING,
		LEAN,
		SHOOT
	};

	State lastState;
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

	Camera* camera = new Camera();
	AnimatedSprite* sprite = new AnimatedSprite();
	AnimatedSprite* gunHeldSprite = new AnimatedSprite();

	CollisionRect* collisionRect = new CollisionRect();

	float defaultCameraSpeed = 8;
	float leanCameraSpeed = 3;

	int cameraLeanOffsetAmount = 40;
	int cameraLeanRaycastLength = 16;
	Raycast* cameraLeanRaycast = new Raycast();
	TimerNode* cameraLeanTimer = new TimerNode();

	int currentWeaponIndex = -1;
	List<Item*> weapons;


	void cameraLeanTimerTimeout();

	void stateEntered(State state);
	void stateExited(State state);
	void stateUpdate(State state);
	void statePhysicsUpdate(State state);
	void calculateMovement();

	void onItemPickup(Item* item) override;
	void onItemSwitched(Item* item) override;
	void onItemUsed(Item* item) override;

	void onWeaponPickup(Item* weapon);
	void onWeaponSwitched(Item* weapon);
	void onWeaponUsed(Item* weapon);

	//void onWeaponPickup(Item* item);
	//void useWeapon();

	//void nextWeapon();
	//Item* getCurrentWeapon();


public:
	Player(std::string name = "Player");

	ItemsHUD* itemsHUD;

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;
};
