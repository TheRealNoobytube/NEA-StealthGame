#include "Player.h"

Player::Player(std::string name) : Entity(name) {
	addChild(&sprite);
	addChild(&collisionRect);
	addChild(&camera);
	addChild(&cameraLeanRaycast);
	addChild(&cameraLeanTimer);
}

void Player::ready() {
	__super::ready();

	this->speed = 1;

	collisionRect.position = Vector2D(-3, -6);
	collisionRect.setSize(Vector2D(8, 17));
	collisionRect.visible = false;

	sprite.position = Vector2D(-7, -15);
	sprite.visible = true;

	int animationFps = 14;

	sprite.setTexture(getSceneTree()->getBasePath() + "../Assets/Player/Player.png");
	sprite.setHFrames(9);
	sprite.setVFrames(5);

	sprite.createAnimation("IdleUp", { 0 }, false);
	sprite.createAnimation("MoveUp", { 1,2,3,4,5,6,7,8 }, false, false, animationFps, true);

	sprite.createAnimation("IdleUpRight", { 9 }, false);
	sprite.createAnimation("MoveUpRight", { 10,11,12,13,14,15,16,17 }, false, false, animationFps, true);
	sprite.createAnimation("IdleUpLeft", { 9 }, true);
	sprite.createAnimation("MoveUpLeft", { 10,11,12,13,14,15,16,17 }, true, false, animationFps, true);

	sprite.createAnimation("IdleRight", { 18 }, false);
	sprite.createAnimation("MoveRight", { 19,20,21,22,23,24,25,26 }, false, false, animationFps, true);
	sprite.createAnimation("IdleLeft", { 18 }, true);
	sprite.createAnimation("MoveLeft", { 19,20,21,22,23,24,25,26 }, true, false, animationFps, true);

	sprite.createAnimation("IdleDownRight", { 27 }, false);
	sprite.createAnimation("MoveDownRight", { 28,29,30,31,32,33,34,35 }, false, false, animationFps, true);
	sprite.createAnimation("IdleDownLeft", { 27 }, true);
	sprite.createAnimation("MoveDownLeft", { 28,29,30,31,32,33,34,35 }, true, false, animationFps, true);

	sprite.createAnimation("IdleDown", { 36 }, false);
	sprite.createAnimation("MoveDown", { 37,38,39,40,41,42,43,44 }, false, false, animationFps, true);

	cameraLeanRaycast.position = Vector2D(1, 0);
	cameraLeanRaycast.targetPosition = Vector2D(0, -cameraLeanRaycastLength);
	cameraLeanRaycast.visible = false;
	cameraLeanRaycast.mask = WORLD ;

	cameraLeanTimer.loop = false;
	cameraLeanTimer.setLength(0.5);
	cameraLeanTimer.timeout.connect([this]() { cameraLeanTimerTimeout(); });


	SDL_SetRenderTarget(getSceneTree()->getRenderer(), sprite.getTexture()->getTexture());
}




void Player::update(float delta) {
	__super::update(delta);

	if (nextState != currentState) {
		stateExited(currentState);
		currentState = nextState;
		stateEntered(nextState);
		
	}

	stateUpdate(currentState);
}

void Player::physicsUpdate(float delta) {
	__super::physicsUpdate(delta);
	//only do physics operations such as movement inside of physicsUpdate
	//this function is called at a fixed frame rate meaning slowdown and speedups won't occur
	//this means physics is more consistent and reliable

	//the applyVelocity function returns a bool, letting us know if the entity collided with anything when trying to move
	//we can use this to slow down the player's animations when they're colliding, gives the user some visual feedback that they need to move out of the way

	if (movement.applyVelocity()) {
		sprite.setSpeedScale(0.5);
		isColliding = true;
	}
	else {
		sprite.setSpeedScale(1);
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

		camera.setCameraSpeed(leanCameraSpeed);
		break;
	}
}



void Player::stateExited(State state) {

	switch (state) {
	case(MOVING):
		cameraLeanTimer.stop();
		break;

	case(LEAN):

		camera.setCameraSpeed(defaultCameraSpeed);
		camera.offset = Vector2D(0, 0);
		break;
	}
}

void Player::stateUpdate(State state) {
	std::string stateName = "Idle";

	switch (state) {
	case(IDLE): 
		stateName = "Idle"; 

		calculateMovement();

		if (movement.direction.x != 0 || movement.direction.y != 0) {
			nextState = MOVING;
		}

		break;

	case(MOVING): 
		stateName = "Move"; 

		cameraLeanRaycast.targetPosition = Vector2D(movement.direction.x * cameraLeanRaycastLength, movement.direction.y * cameraLeanRaycastLength);


		if (cameraLeanRaycast.isColliding() && (vertical == V_NONE || horizontal == H_NONE)) {
			if (!cameraLeanTimer.isRunning()) {
				cameraLeanTimer.start();
			}
		}
		else {
			cameraLeanTimer.stop();
		}

		calculateMovement();

		if (movement.direction == Vector2D(0, 0)) {
			nextState = IDLE;
		}

		break;

	case(LEAN):

		calculateMovement();

		if (movement.direction == Vector2D(0, 0) || !cameraLeanRaycast.isColliding()) {
			nextState = IDLE;
		}


		if (cameraLeanRaycast.getContactNormal().x != 0) {
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

		camera.offset.x = cameraLeanOffsetAmount * -movement.direction.x;
		camera.offset.y = cameraLeanOffsetAmount * -movement.direction.y;

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

	sprite.play(stateName + walkDirection);
}



void Player::calculateMovement() {
	//the D key is the right direction, which is positive, so we subtract by the left direction, key A
	movement.direction.x = (isKeyPressed(SDL_SCANCODE_D) || isKeyPressed(SDL_SCANCODE_RIGHT)) - (isKeyPressed(SDL_SCANCODE_A) || isKeyPressed(SDL_SCANCODE_LEFT));

	//the S key is the down direction, which is positive, so we subtract by the up direction, key S
	movement.direction.y = (isKeyPressed(SDL_SCANCODE_S) || isKeyPressed(SDL_SCANCODE_DOWN)) - (isKeyPressed(SDL_SCANCODE_W) || isKeyPressed(SDL_SCANCODE_UP));

	//only want the direction of the vector so we normalize it, the magnitude is the speed we multiply later which gives us the velocity
	movement.direction = movement.direction.normalized();

	movement.velocity.x = speed * movement.direction.x;
	movement.velocity.y = speed * movement.direction.y;

	//get the current walkingDirection, used for animations
	HorizontalDirection lastHorizontal = horizontal;
	VerticalDirection lastVertical = vertical;

	if (movement.direction.x > 0) {
		horizontal = RIGHT;
	}
	else if(movement.direction.x < 0){
		horizontal = LEFT;
	}
	else {
		horizontal = H_NONE;
	}

	if (movement.direction.y > 0) {
		vertical = DOWN;
	}
	else if (movement.direction.y < 0) {
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