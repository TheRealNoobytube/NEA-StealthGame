#include "Player.h"

Player::Player(std::string name) : Node2D(name){
	addChild(&sprite);
	addChild(&animations);
}

//TODO create an AnimationPlayer class for animations and also do the write up i guess
// A class where you can add animation frames, give a time when they happen and say what changes when it happens
// pointer to the variable to be changed and then the new value when the time is reached
// 
// mention normalization, c++ booleans and how they can be used as numbers, how animations work



void Player::ready() {
	sprite.setTexture(getSceneTree()->getBasePath() + "../Assets/Player/Player.png");
	sprite.setHFrames(9);
	sprite.setVFrames(5);

	Animation* walkingRight = new Animation("WalkingRight");
	walkingRight->loop = true;
	auto wrFrames = walkingRight->createTrack(&sprite.frame);
	wrFrames->insertKey(0, 0);
	wrFrames->insertKey(0.5, 15);

	animations.addAnimation(walkingRight);
	animations.play("WalkingRight");

}

void Player::update(float delta) {
	//in c++, booleans are just 1's or 0's representing true or false respectively, so we can use booleans in place of integers
	// 
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

	if (walking) {
		if (animationTimer >= (60 / fps) ) {
			//switch (walkDirection) {
			//case WALKING_RIGHT:
			//	sprite.flipH = false;
			//	sprite.frame = ((2 * 9) + walkingFrame); break;
			//case WALKING_UP_RIGHT:
			//	sprite.flipH = false;
			//	sprite.frame = ((1 * 9) + walkingFrame); break;
			//case WALKING_UP:
			//	sprite.frame = ((0 * 9) + walkingFrame);break;
			//case WALKING_UP_LEFT:
			//	sprite.flipH = true;
			//	sprite.frame = ((1 * 9) + walkingFrame); break;
			//case WALKING_LEFT:
			//	sprite.flipH = true;
			//	sprite.frame = ((2 * 9) + walkingFrame); break;
			//case WALKING_DOWN_LEFT:
			//	sprite.flipH = true;
			//	sprite.frame = ((3 * 9) + walkingFrame); break;
			//case WALKING_DOWN:
			//	sprite.frame = ((4 * 9) + walkingFrame); break;
			//case WALKING_DOWN_RIGHT:
			//	sprite.flipH = false;
			//	sprite.frame = ((3 * 9) + walkingFrame);break;
			//}

			walkingFrame = ((walkingFrame) % 8) + 1;
		}
		animationTimer = (animationTimer % (60 / fps)) + 1;
	}

	else {
		//switch (walkDirection) {
		//case WALKING_RIGHT:
		//	sprite.frame = ((2 * 9));break;
		//case WALKING_UP_RIGHT:
		//	sprite.frame = ((1 * 9));break;
		//case WALKING_UP:
		//	sprite.frame = ((0 * 9));break;
		//case WALKING_UP_LEFT:
		//	sprite.frame = ((1 * 9));break;
		//case WALKING_LEFT:
		//	sprite.frame = ((2 * 9));break;
		//case WALKING_DOWN_LEFT:
		//	sprite.frame = ((3 * 9));break;
		//case WALKING_DOWN:
		//	sprite.frame = ((4 * 9));break;
		//case WALKING_DOWN_RIGHT:
		//	sprite.frame = ((3 * 9));break;
		//}
		animationTimer = 60 / fps;
		walkingFrame = 1;
	}
}