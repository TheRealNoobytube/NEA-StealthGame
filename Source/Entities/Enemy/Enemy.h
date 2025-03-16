#pragma once
#include "Source/Entities/Entity.h"
#include "Source/Entities/Player/Player.h"

class Pathfinding;

class Enemy : public Entity {
public:
	enum State {
		IDLE,
		PATROLLING,
		CHASING,
		NOTICE,
		ALERT,
		SHOOT
	};

	Level* level;

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


	float shootDistance = 60;

	int idleTime = 0;
	int maxIdleTime = 120;

	int alertTime = 0;
	int maxAlertTime = 30;

	List<Vector2D> patrolPoints;
	int currentPatrolIndex = 0;

	VerticalDirection vertical = UP;
	HorizontalDirection horizontal = H_NONE;

	Pathfinding* pathfinding;
	Player* player;

	TimerNode* pathTimer = new TimerNode();

	AnimatedSprite* sprite = new AnimatedSprite();
	CollisionRect* collision = new CollisionRect();

	Sprite* detectionIcon = new Sprite();

	Vector2D lastPlayerPosition = Vector2D(0, 0);

	Raycast* lineOfSightCast = new Raycast();
	Raycast* detectionCastOne = new Raycast();
	Raycast* detectionCastTwo = new Raycast();
	Raycast* noticeCastOne = new Raycast();
	Raycast* noticeCastTwo = new Raycast();
	float detectionRange = 60;
	float noticeRange = 120;


	bool disableAI = false;

	Enemy(std::string name = "Enemy");

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;


	bool isDetectingPlayer();
	bool isNoticingPlayer();
	
	void foundPlayer();
	void lostPlayer();
	void endPursuit();


	void stateEntered(State state);
	void stateExited(State state);
	void stateUpdate(State state);
	void statePhysicsUpdate(State state);
	void calculateMovement();

	void onPathTimerTimeout();

	void onDamaged(float damage) override;
	void onDeath(float damage) override;


	void onTargetReached();
};

#include "Source/Pathfinding/Pathfinding.h"
