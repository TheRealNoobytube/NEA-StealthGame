#include "Player.h"

Player::Player(std::string name) : Entity(name) {
	addChild(sprite);
	addChild(gunHeldSprite);
	addChild(collisionRect);
	addChild(camera);
	addChild(cameraLeanRaycast);
	addChild(cameraLeanTimer);
}

void Player::ready() {
	__super::ready();

	this->speed = 3;

	layer = layer | PLAYER;

	collisionRect->setSize(Vector2D(8, 17));
	collisionRect->position = Vector2D(-collisionRect->getSize().x / 2, -collisionRect->getSize().y / 2);
	collisionRect->visible = false;

	sprite->position = Vector2D(-8, -16);
	sprite->visible = true;

	gunHeldSprite->position = Vector2D(-8, -16);
	gunHeldSprite->visible = false;

	int animationFps = 14;

	sprite->setTexture(getSceneTree()->getBasePath() + "../Assets/Player/Player.png");
	sprite->setHFrames(9);
	sprite->setVFrames(5);

	sprite->createAnimation("IdleUp", { 0 }, false);
	sprite->createAnimation("MoveUp", { 1,2,3,4,5,6,7,8 }, animationFps, false, false, true);

	sprite->createAnimation("IdleUpRight", { 9 }, false);
	sprite->createAnimation("MoveUpRight", { 10,11,12,13,14,15,16,17 }, animationFps, false, false, true);
	sprite->createAnimation("IdleUpLeft", { 9 }, animationFps, true);
	sprite->createAnimation("MoveUpLeft", { 10,11,12,13,14,15,16,17 }, animationFps, true, false, true);

	sprite->createAnimation("IdleRight", { 18 }, false);
	sprite->createAnimation("MoveRight", { 19,20,21,22,23,24,25,26 }, animationFps, false, false, true);
	sprite->createAnimation("IdleLeft", { 18 }, animationFps, true);
	sprite->createAnimation("MoveLeft", { 19,20,21,22,23,24,25,26 },  animationFps, true, false, true);

	sprite->createAnimation("IdleDownRight", { 27 }, false);
	sprite->createAnimation("MoveDownRight", { 28,29,30,31,32,33,34,35 }, animationFps, false, false, true);
	sprite->createAnimation("IdleDownLeft", { 27 }, animationFps, true);
	sprite->createAnimation("MoveDownLeft", { 28,29,30,31,32,33,34,35 }, animationFps, true, false, true);

	sprite->createAnimation("IdleDown", { 36 }, false);
	sprite->createAnimation("MoveDown", { 37,38,39,40,41,42,43,44 }, animationFps, false, false, true);



	gunHeldSprite->animationFinished.connect([this]() { if (currentState == SHOOT) { nextState = lastState; } });

	gunHeldSprite->setTexture(getSceneTree()->getBasePath() + "../Assets/Player/PlayerGunHeld.png");
	gunHeldSprite->setHFrames(4);
	gunHeldSprite->setVFrames(5);

	gunHeldSprite->createAnimation("IdleUp", { 0 }, animationFps, false);
	gunHeldSprite->createAnimation("IdleUpRight", { 4 }, animationFps, false);
	gunHeldSprite->createAnimation("IdleUpLeft", { 4 }, animationFps, true);
	gunHeldSprite->createAnimation("IdleRight", { 8 }, animationFps, false);
	gunHeldSprite->createAnimation("IdleLeft", { 8 }, animationFps, true);
	gunHeldSprite->createAnimation("IdleDownRight", { 12 }, animationFps, false);
	gunHeldSprite->createAnimation("IdleDownLeft", { 12 }, animationFps, true);
	gunHeldSprite->createAnimation("IdleDown", { 16 }, animationFps, false);

	gunHeldSprite->createAnimation("ShootUp", { 1, 2, 3 }, animationFps, false);
	gunHeldSprite->createAnimation("ShootUpRight", { 5, 6, 7 }, animationFps, false);
	gunHeldSprite->createAnimation("ShootUpLeft", { 5, 6, 7 }, animationFps, true);
	gunHeldSprite->createAnimation("ShootRight", { 9, 10, 11 }, animationFps, false);
	gunHeldSprite->createAnimation("ShootLeft", { 9, 10, 11 }, animationFps, true);
	gunHeldSprite->createAnimation("ShootDownRight", { 13, 14, 15 }, animationFps, false);
	gunHeldSprite->createAnimation("ShootDownLeft", { 13, 14, 15 }, animationFps, true);
	gunHeldSprite->createAnimation("ShootDown", { 17, 18, 19 }, animationFps, false);


	cameraLeanRaycast->position = Vector2D(0, 0);
	cameraLeanRaycast->targetPosition = Vector2D(0, -cameraLeanRaycastLength);
	cameraLeanRaycast->visible = false;
	cameraLeanRaycast->mask = WORLD;

	cameraLeanTimer->loop = false;
	cameraLeanTimer->setLength(0.5);
	cameraLeanTimer->timeout.connect([this]() { cameraLeanTimerTimeout(); });
}


void Player::update(float delta) {
	__super::update(delta);

	if (isKeyJustPressed(SDL_SCANCODE_LCTRL)) {
		weaponInventory->nextItem();
	}

	if (isKeyJustPressed(SDL_SCANCODE_LSHIFT)) {
		itemInventory->nextItem();
	}

	if (isKeyJustPressed(SDL_SCANCODE_SPACE)) {
		itemInventory->useCurrentItem();
	}

	stateUpdate(currentState);


	drawRect(getGlobalPosition(), Vector2D(1, 1), Color(255, 255, 255));
}

//only do physics operations such as movement inside of physicsUpdate
//this function is called at a fixed frame rate meaning slowdown and speedups won't occur
//this means physics is more consistent and reliable
void Player::physicsUpdate(float delta) {
	__super::physicsUpdate(delta);

	if (nextState != currentState) {
		stateExited(currentState);
		lastState = currentState;
		currentState = nextState;
		stateEntered(nextState);
	}

	statePhysicsUpdate(currentState);


	if (!movement->applyVelocity().isEmpty()) {
		sprite->setSpeedScale(0.5);
		isColliding = true;
	}
	else {
		sprite->setSpeedScale(1);
		isColliding = false;
	}
}


void Player::cameraLeanTimerTimeout() {
	nextState = LEAN;
}



void Player::stateEntered(State state) {

	switch (state) {
	case(IDLE):
		break;

	case(MOVING):
		break;

	case(LEAN):
		camera->setCameraSpeed(leanCameraSpeed);
		break;
	case(SHOOT):
		gunHeldSprite->stop();
		movement->velocity = Vector2D(0, 0);
		break;
	}


}



void Player::stateExited(State state) {

	switch (state) {
	case(IDLE):
		break;

	case(MOVING):
		cameraLeanTimer->stop();
		break;

	case(LEAN):
		camera->setCameraSpeed(defaultCameraSpeed);
		camera->offset = Vector2D(0, 0);
		break;
	}
}

void Player::stateUpdate(State state) {

	switch (state) {
	case(IDLE):

		if (weaponInventory->getCurrentItem() != nullptr) {
			if (isMouseButtonJustPressed(SDL_BUTTON_LEFT)) {
				weaponInventory->useCurrentItem();
			}
		}

		break;


	case(MOVING):

		if (weaponInventory->getCurrentItem() != nullptr) {
			if (isMouseButtonJustPressed(SDL_BUTTON_LEFT)) {
				weaponInventory->useCurrentItem();
			}
		}
		break;
	}
}






void Player::statePhysicsUpdate(State state) {
	std::string stateName = "Idle";
	bool switchToGunSprite = false;


	switch (state) {
	case(IDLE): 
		stateName = "Idle"; 

		calculateMovement();

		switchToGunSprite = (weaponInventory->getCurrentItem() != nullptr);

		if (movement->direction.x != 0 || movement->direction.y != 0) {
			nextState = MOVING;
		}

		break;



	case(MOVING): 
		stateName = "Move"; 

		cameraLeanRaycast->targetPosition = Vector2D(movement->direction.x * cameraLeanRaycastLength, movement->direction.y * cameraLeanRaycastLength);

		calculateMovement();

		if (cameraLeanRaycast->isColliding() && (vertical == V_NONE || horizontal == H_NONE)) {
			if (!cameraLeanTimer->isRunning()) {
				cameraLeanTimer->start();
			}
		}
		else {
			cameraLeanTimer->stop();
		}

		if (movement->direction == Vector2D(0, 0)) {
			nextState = IDLE;
		}


		break;



	case(LEAN):
		calculateMovement();

		cameraLeanRaycast->targetPosition = Vector2D(movement->direction.x * cameraLeanRaycastLength, movement->direction.y * cameraLeanRaycastLength);

		camera->offset.x = cameraLeanOffsetAmount * -movement->direction.x;
		camera->offset.y = cameraLeanOffsetAmount * -movement->direction.y;

		if (cameraLeanRaycast->getContactNormal().x != 0) {
			if (horizontal == RIGHT) {
				horizontal = LEFT;
			}
			else if (horizontal == LEFT) {
				horizontal = RIGHT;
			}
		}
		else {
			if (vertical == UP) {
				vertical = DOWN;
			}
			else if (vertical == DOWN) {
				vertical = UP;
			}
		}

		if (movement->direction == Vector2D(0, 0) || !cameraLeanRaycast->isColliding()) {
			nextState = IDLE;
		}

		break;



	case(SHOOT):
		stateName = "Shoot";
		switchToGunSprite = true;

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


	if (switchToGunSprite) {
		sprite->visible = false;
		gunHeldSprite->visible = true;
		gunHeldSprite->play(stateName + walkDirection);
	}
	else {
		gunHeldSprite->visible = false;
		sprite->visible = true;
		sprite->play(stateName + walkDirection);
	}
}



void Player::calculateMovement() {
	//the D key is the right direction, which is positive, so we subtract by the left direction, key A
	movement->direction.x = (isKeyPressed(SDL_SCANCODE_D) || isKeyPressed(SDL_SCANCODE_RIGHT)) - (isKeyPressed(SDL_SCANCODE_A) || isKeyPressed(SDL_SCANCODE_LEFT));

	//the S key is the down direction, which is positive, so we subtract by the up direction, key S
	movement->direction.y = (isKeyPressed(SDL_SCANCODE_S) || isKeyPressed(SDL_SCANCODE_DOWN)) - (isKeyPressed(SDL_SCANCODE_W) || isKeyPressed(SDL_SCANCODE_UP));

	//only want the direction of the vector so we normalize it, the magnitude is the speed we multiply later which gives us the velocity
	movement->direction = movement->direction.normalized();

	movement->velocity.x = speed * movement->direction.x;
	movement->velocity.y = speed * movement->direction.y;



	//get the current walkingDirection, used for animations
	HorizontalDirection lastHorizontal = horizontal;
	VerticalDirection lastVertical = vertical;

	if (movement->direction.x > 0) {
		horizontal = RIGHT;
	}
	else if(movement->direction.x < 0){
		horizontal = LEFT;
	}
	else {
		horizontal = H_NONE;
	}

	if (movement->direction.y > 0) {
		vertical = DOWN;
	}
	else if (movement->direction.y < 0) {
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



void Player::onItemPickup(Item* item) {
	if (!itemsHUD->showingItem() || itemsHUD->getCurrentItemID() == item->getItemID()) {
		itemsHUD->changeItemIcon(item, false);
	}
}

void Player::onItemSwitched(Item* item) {
	itemsHUD->changeItemIcon(item);
}

void Player::onItemUsed(Item* item) {
	if (itemInventory->getCurrentItemIndex() == -1) {
		itemsHUD->hideItemIcon();
	}
	else {
		itemsHUD->changeItemIcon(item, false);
	}

}


void Player::onWeaponPickup(Item* weapon) {
	if (!itemsHUD->showingWeapon() || itemsHUD->getCurrentWeaponID() == weapon->getItemID()) {
		itemsHUD->changeWeaponIcon(weapon, false);
	}
}

void Player::onWeaponSwitched(Item* weapon) {
	itemsHUD->changeWeaponIcon(weapon);
}

void Player::onWeaponUsed(Item* weapon) {
	if (weaponInventory->getCurrentItemIndex() == -1) {
		itemsHUD->hideWeaponIcon();
	}
	else {
		itemsHUD->changeWeaponIcon(weapon, false);
		nextState = SHOOT;
	}
}

