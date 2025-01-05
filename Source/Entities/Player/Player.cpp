#include "Player.h"

Player::Player(std::string name) : Node2D(name){
	addChild(&sprite);
}

//write up notes:
// 
// mention normalization, 
// c++ booleans and how they can be used as numbers,
// how animations work
// updating the list data structure: the rule of three, variadic args

void Player::ready() {
	sprite.setTexture(getSceneTree()->getBasePath() + "../Assets/Player/Player.png");
	sprite.setHFrames(9);
	sprite.setVFrames(5);

	int animationFps = 16;

	sprite.createAnimation("IdleUp", { 0 });
	sprite.createAnimation("MoveUp", { 1,2,3,4,5,6,7,8 }, animationFps, true);

	sprite.createAnimation("IdleUpRight", { 9 });
	sprite.createAnimation("MoveUpRight", { 10,11,12,13,14,15,16,17 }, animationFps, true);

	sprite.createAnimation("IdleRight", { 18 });
	sprite.createAnimation("MoveRight", { 19,20,21,22,23,24,25,26 }, animationFps, true);

	sprite.createAnimation("IdleDownRight", { 27 });
	sprite.createAnimation("MoveDownRight", { 28,29,30,31,32,33,34,35 }, animationFps, true);

	sprite.createAnimation("IdleDown", { 36 });
	sprite.createAnimation("MoveDown", { 37,38,39,40,41,42,43,44 }, animationFps, true);
}

void Player::update(float delta) {
	//in c++, booleans are just 1's or 0's representing true or false respectively, so we can use booleans in place of integers
	
	//the D key is the right direction, which is positive, so we subtract by the left direction, key A
	direction.x = isKeyPressed(SDL_SCANCODE_D) - isKeyPressed(SDL_SCANCODE_A);
	//the S key is the down direction, which is positive, so we subtract by the up direction, key S
	direction.y = isKeyPressed(SDL_SCANCODE_S) - isKeyPressed(SDL_SCANCODE_W);

	//get the current walkingDirection, used for animations
	if (direction.x == 1 && direction.y == 0) {
		walkDirection = WALKING_RIGHT;
	}
	else if (direction.x == 1 && direction.y == -1) {
		walkDirection = WALKING_UP_RIGHT;
	}
	else if (direction.x == 0 && direction.y == -1) {
		walkDirection = WALKING_UP;
	}
	else if (direction.x == -1 && direction.y == -1) {
		walkDirection = WALKING_UP_LEFT;
	}
	else if (direction.x == -1 && direction.y == 0) {
		walkDirection = WALKING_LEFT;
	}
	else if (direction.x == -1 && direction.y == 1) {
		walkDirection = WALKING_DOWN_LEFT;
	}
	else if (direction.x == 0 && direction.y == 1) {
		walkDirection = WALKING_DOWN;
	}
	else if (direction.x == 1 && direction.y == 1) {
		walkDirection = WALKING_DOWN_RIGHT;
	}

	walking = (direction.x != 0 || direction.y != 0); //walking only true when the x or y direction don't equal 0
	
	//only want the direction of the vector so we normalize it, the magnitude is the speed we multiply later which gives us the velocity
	direction = direction.normalized(); 

	velocity.x = speed * direction.x;
	velocity.y = speed * direction.y;
}

void Player::physicsUpdate(float delta) {
	//only do physics operations such as movement inside of physicsUpdate
	//this function is called at a fixed frame rate meaning slowdown and speedups won't occur
	//this means physics is more consistent and reliable
	position.x += velocity.x;
	position.y += velocity.y;

	std::string state = "Idle";

	if (walking) {
		state = "Move";
	}

	switch (walkDirection) {
	case WALKING_RIGHT:
		sprite.flipH = false;
		sprite.play(state + "Right"); break;
	case WALKING_UP_RIGHT:
		sprite.flipH = false;
		sprite.play(state + "UpRight"); break;
	case WALKING_UP:
		sprite.play(state + "Up"); break;
	case WALKING_UP_LEFT:
		sprite.flipH = true;
		sprite.play(state + "UpRight"); break;
	case WALKING_LEFT:
		sprite.flipH = true;
		sprite.play(state + "Right"); break;
	case WALKING_DOWN_LEFT:
		sprite.flipH = true;
		sprite.play(state + "DownRight"); break;
	case WALKING_DOWN:
		sprite.play(state + "Down"); break;
	case WALKING_DOWN_RIGHT:
		sprite.flipH = false;
		sprite.play(state + "DownRight"); break;
	}
}