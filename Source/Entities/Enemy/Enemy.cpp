#include "Enemy.h"

Enemy::Enemy(std::string name) : Entity(name){
	addChild(sprite);
	addChild(collision);
	pathfinding = new Pathfinding();
	addChild(pathfinding);
	addChild(pathTimer);

	addChild(detectionIcon);
	addChild(detectionCastOne);
	addChild(detectionCastTwo);

	addChild(noticeCastOne);
	addChild(noticeCastTwo);

	addChild(lineOfSightCast);
}

void Enemy::ready() {
	__super::ready();

	auto level = dynamic_cast<Level*>(getSceneTree()->getCurrentScene());

	if (level != nullptr) {
		this->player = level->currentPlayer;
		this->level = level;
	}

	this->speed = 0.9;

	mask = 0;


	Pistol* pistol = new Pistol();
	pistol->enemyItem = true;
	addChild(pistol);
	pistol->useSpeed = 2;
	
	weaponInventory->onItemPickup(pistol);
	

	pathTimer->setLength(0.8);
	pathTimer->timeout.connect([this]() { this->onPathTimerTimeout(); });
	pathTimer->loop = true;
	pathTimer->start();

	pathfinding->desiredDistanceToPoint = 3;
	pathfinding->target_reached.connect([this]() { onTargetReached(); });

	collision->visible = false;
	collision->setSize(Vector2D(6, 11));
	collision->position = Vector2D(-collision->getSize().x / 2, -collision->getSize().y / 2);
	collision->position.y -= 2;

	sprite->position = Vector2D(-8, -16);
	sprite->visible = true;
	sprite->setTexture(getSceneTree()->getBasePath() + "../Assets/Enemies/Enemy.png");
	sprite->setHFrames(6);
	sprite->setVFrames(5);

	int animationFps = 10;

	sprite->createAnimation("IdleUp", { 0 }, animationFps, false);
	sprite->createAnimation("MoveUp", { 1,2,3,4,5 }, animationFps, false, false, true);

	sprite->createAnimation("IdleUpRight", { 6 }, animationFps, false);
	sprite->createAnimation("MoveUpRight", { 7,8,9,10,11 }, animationFps, false, false, true);
	sprite->createAnimation("IdleUpLeft", { 6 }, animationFps, true);
	sprite->createAnimation("MoveUpLeft", { 7,8,9,10,11 }, animationFps, true, false, true);

	sprite->createAnimation("IdleRight", { 12 }, animationFps, false);
	sprite->createAnimation("MoveRight", { 13,14,15,16,17 }, animationFps, false, false, true);
	sprite->createAnimation("IdleLeft", { 12 }, animationFps, true);
	sprite->createAnimation("MoveLeft", { 13,14,15,16,17 }, animationFps, true, false, true);

	sprite->createAnimation("IdleDownRight", { 18 }, animationFps, false);
	sprite->createAnimation("MoveDownRight", { 19,20,21,22,23 },animationFps, false, false, true);
	sprite->createAnimation("IdleDownLeft", { 18 }, animationFps, true);
	sprite->createAnimation("MoveDownLeft", { 19,20,21,22,23 }, animationFps, true, false, true);

	sprite->createAnimation("IdleDown", { 24 }, animationFps, false);
	sprite->createAnimation("MoveDown", { 25,26,27,28,29 }, animationFps, false, false, true);

	detectionIcon->setTexture(getSceneTree()->getBasePath() + "../Assets/Enemies/DetectionIcons.png");
	detectionIcon->visible = false;
	detectionIcon->setHFrames(2);
	detectionIcon->position = Vector2D(-7.5, -28);

	detectionCastOne->position = Vector2D(-0.5, 0);
	detectionCastOne->mask = ENTITIES | WORLD;

	detectionCastTwo->position = Vector2D(-0.5, 0);
	detectionCastTwo->mask = ENTITIES | WORLD;

	noticeCastOne->position = Vector2D(-0.5, 0);
	noticeCastOne->mask = ENTITIES | WORLD;

	noticeCastTwo->position = Vector2D(-0.5, 0);
	noticeCastTwo->mask = ENTITIES | WORLD;

	lineOfSightCast->position = Vector2D(-0.5, 0);
	lineOfSightCast->mask = ENTITIES | WORLD;
}

void Enemy::update(float delta) {
	__super::update(delta);

	stateUpdate(currentState);
}

void Enemy::physicsUpdate(float delta) {
	__super::physicsUpdate(delta);

	if (nextState != currentState) {
		stateExited(currentState);
		lastState = currentState;
		currentState = nextState;
		stateEntered(nextState);
	}

	statePhysicsUpdate(currentState);
}


void Enemy::stateEntered(State state) {

	switch (state) {
	case(PATROLLING): speed = 0.5; break;
	case(NOTICE): 
		speed = 0.6;
		pathTimer->start(0);
		pathfinding->currentPath.clear(); 
		detectionIcon->visible = true;
		detectionIcon->frame = 1;
		lastPlayerPosition = player->position;
		
		break;

	case(ALERT):
		speed = 0.8;
		detectionIcon->visible = true;
		detectionIcon->frame = 0;
		alertTime = 0;

		break;

	case(CHASING):
		pathTimer->start(0);
		pathfinding->currentPath.clear();
		detectionIcon->visible = false;
		level->startChase();


		break;
	case(SHOOT):

		movement->direction = position.directionTo(player->position);
		calculateMovement();
		weaponInventory->useCurrentItem();

		nextState = CHASING;
		break;
	}
	

}

void Enemy::stateExited(State state) {

	switch (state) {
	case(NOTICE):
		detectionIcon->visible = false;
		break;
	case(CHASING):
		detectionIcon->visible = false;
		break;

	}


}

void Enemy::stateUpdate(State state) {

}

void Enemy::statePhysicsUpdate(State state) {
	std::string stateName = "Idle";

	switch (state) {
	case(IDLE):
		idleTime++;

		if (!disableAI) {
			isDetectingPlayer();
			if (isNoticingPlayer()) {
				nextState = NOTICE;
			}
		}

		break;
	case(PATROLLING):
		stateName = "Move";

		if (!disableAI) {
			pathfinding->followPath(this);
			calculateMovement();

			if (isDetectingPlayer()) {
				foundPlayer();
			}
			if (isNoticingPlayer()) {
				nextState = NOTICE;
			}
		}

		break;
	case(NOTICE):
		stateName = "Move";
		if (!disableAI) {
			pathfinding->followPath(this);
			calculateMovement();

			if (isDetectingPlayer()) {
				foundPlayer();
			}
		}
		break;


	case(ALERT):

		alertTime++;
		if (alertTime >= maxAlertTime) {
			nextState = CHASING;
		}


		break;

	case (CHASING):
		stateName = "Move";

		if (!disableAI) {

			if (!isDetectingPlayer()) {
				if (!level->chaseTimer->isRunning()) {
					level->chaseTimer->start();
				}

				pathfinding->followPath(this);
				calculateMovement();
			}


			else {
				if (position.distanceTo(player->position) > shootDistance) {
					pathfinding->followPath(this);
					calculateMovement();
				}
				else {
					if (!weaponInventory->isItemOnCooldown()) {
						nextState = SHOOT;
					}
				}

				level->chaseTimer->stop();
			}
		}

		break;
	}

	std::string walkDirection;

	switch (vertical) {
	case(UP):walkDirection += "Up"; break;
	case(DOWN):walkDirection += "Down"; break;
	}

	switch (horizontal) {
	case(LEFT):walkDirection += "Left"; break;
	case(RIGHT):walkDirection += "Right"; break;
	}

	sprite->play(stateName + walkDirection);
}



void Enemy::calculateMovement() {
	//get the current walkingDirection, used for animations
	HorizontalDirection lastHorizontal = horizontal;
	VerticalDirection lastVertical = vertical;

	Vector2D fixedDirection = movement->direction.fixDirection();


	if (fixedDirection.x > 0) {
		horizontal = RIGHT;
	}
	else if (fixedDirection.x < 0) {
		horizontal = LEFT;
	}
	else {
		horizontal = H_NONE;
	}

	if (fixedDirection.y > 0) {
		vertical = DOWN;
	}
	else if (fixedDirection.y < 0) {
		vertical = UP;
	}
	else {
		vertical = V_NONE;
	}

	if (horizontal == H_NONE && vertical == V_NONE) {
		horizontal = lastHorizontal;
		vertical = lastVertical;
	}
}



void Enemy::onPathTimerTimeout() {
	if (!disableAI) {

		if (idleTime > maxIdleTime) {
			idleTime = 0;
			nextState = PATROLLING;
			if (!patrolPoints.isEmpty()) {

				pathfinding->findPath(position, patrolPoints.get(currentPatrolIndex));
			}
		}

		if (currentState == PATROLLING) {
			if (!patrolPoints.isEmpty()) {

				pathfinding->findPath(position, patrolPoints.get(currentPatrolIndex));
			}
		}
		else if (currentState == NOTICE) {
			if (!pathfinding->findPath(position, lastPlayerPosition)) {
				nextState = IDLE;
			}
		}
		else if (currentState == CHASING) {
			pathfinding->findPath(position, player->position);
		}
	}
}

void Enemy::onTargetReached() {
	if (currentState == PATROLLING) {
		if (!patrolPoints.isEmpty()) {
			currentPatrolIndex = (currentPatrolIndex + 1) % patrolPoints.getSize();
			nextState = IDLE;
		}
	}
	else if (currentState == NOTICE) {
		nextState = IDLE;
	}
}


void Enemy::onDamaged(float damage) {
	if (currentState == ALERT) {
		alertTime = -30;
	}
}


void Enemy::onDeath(float damage) {
	queueFree();
}


bool Enemy::isDetectingPlayer() {
	detectionCastOne->targetPosition = Vector2D(movement->direction.x * detectionRange, movement->direction.y * detectionRange);
	detectionCastTwo->targetPosition = Vector2D(movement->direction.x * detectionRange, movement->direction.y * detectionRange);
	lineOfSightCast->targetPosition = Vector2D(movement->direction.x * detectionRange * 1.4, movement->direction.y * detectionRange * 1.4);


	if (horizontal != H_NONE) {
		detectionCastOne->targetPosition.y -= 10;
		detectionCastTwo->targetPosition.y += 10;
	}
	if (vertical != V_NONE) {
		detectionCastOne->targetPosition.x -= 10;
		detectionCastTwo->targetPosition.x += 10;
	}


	if (lineOfSightCast->isColliding()) {
		if (lineOfSightCast->getCollider() == player) {
			return true;
		}
	}
	if (detectionCastOne->isColliding()) {
		if (detectionCastOne->getCollider() == player) {
			return true;
		}
	}
	if (detectionCastTwo->isColliding()) {
		if (detectionCastTwo->getCollider() == player) {
			return true;
		}
	}
	
	
	return false;
}


bool Enemy::isNoticingPlayer() {
	noticeCastOne->targetPosition = Vector2D(movement->direction.x * noticeRange, movement->direction.y * noticeRange);
	noticeCastTwo->targetPosition = Vector2D(movement->direction.x * noticeRange, movement->direction.y * noticeRange);

	for (int i = 0; i < 2; i++) {

		if (horizontal != H_NONE) {
			noticeCastOne->targetPosition.y -= 20;
			noticeCastTwo->targetPosition.y += 20;
		}
		if (vertical != V_NONE) {
			noticeCastOne->targetPosition.x -= 20;
			noticeCastTwo->targetPosition.x += 20;
		}


		noticeCastOne->forceUpdateRaycast();
		noticeCastTwo->forceUpdateRaycast();

		if (noticeCastOne->isColliding()) {
			if (noticeCastOne->getCollider() == player) {
				return true;
			}
		}
		if (noticeCastTwo->isColliding()) {
			if (noticeCastTwo->getCollider() == player) {
				return true;
			}
		}

	}

	return false;
}

void Enemy::foundPlayer() {
	nextState = ALERT;
}

void Enemy::lostPlayer() {
	nextState = NOTICE;
}

void Enemy::endPursuit() {
	nextState = PATROLLING;
}