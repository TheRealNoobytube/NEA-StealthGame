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
		SHOOT,
		DEAD
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


	Rectangle* rect = new Rectangle();

	VerticalDirection vertical = UP;
	HorizontalDirection horizontal = H_NONE;

	bool isColliding = false;

	Camera* camera = new Camera();
	AnimatedSprite* sprite = new AnimatedSprite();
	AnimatedSprite* gunHeldSprite = new AnimatedSprite();
	AnimatedSprite* deathSprite = new AnimatedSprite();

	CollisionRect* collisionRect = new CollisionRect();

	float defaultCameraSpeed = 8;
	float leanCameraSpeed = 3;

	int cameraLeanOffsetAmount = 80;
	int cameraLeanRaycastLength = 16;
	Raycast* cameraLeanRaycast = new Raycast();
	TimerNode* cameraLeanTimer = new TimerNode();

	int currentWeaponIndex = -1;
	List<Item*> weapons;

	void setAnimationDirection();


	void cameraLeanTimerTimeout();

	void stateEntered(State state);
	void stateExited(State state);
	void stateUpdate(State state, float delta);
	void statePhysicsUpdate(State state, float delta);
	void calculateMovement();

	void onItemPickup(Item* item) override;
	void onItemSwitched(Item* item) override;
	void onItemUsed(Item* item) override;

	void onWeaponPickup(Item* weapon);
	void onWeaponSwitched(Item* weapon);
	void onWeaponUsed(Item* weapon);

	void onDamaged(float damage) override;
	void onDeath(float damage) override;


public:
	Player(std::string name = "Player");

	ItemsHUD* itemsHUD;

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;
};
