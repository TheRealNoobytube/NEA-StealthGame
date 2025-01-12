#include "Enemy.h"

Enemy::Enemy(std::string name) : Entity(name){
	addChild(&sprite);
	addChild(&collision);
}

void Enemy::ready() {
	__super::ready();

	collision.visible = false;
	collision.position = Vector2D(4, 8);
	collision.setSize(Vector2D(8, 17));

	sprite.setTexture(getSceneTree()->getBasePath() + "../Assets/Enemies/Enemy.png");
	sprite.setHFrames(6);
	sprite.setVFrames(5);

	int animationFps = 10;

	sprite.createAnimation("IdleUp", { 0 });
	sprite.createAnimation("MoveUp", { 1,2,3,4,5 }, animationFps, true);

	sprite.createAnimation("IdleUpRight", { 6 });
	sprite.createAnimation("MoveUpRight", { 7,8,9,10,11 }, animationFps, true);

	sprite.createAnimation("IdleRight", { 12 });
	sprite.createAnimation("MoveRight", { 13,14,15,16,17 }, animationFps, true);

	sprite.createAnimation("IdleDownRight", { 18 });
	sprite.createAnimation("MoveDownRight", { 19,20,21,22,23 }, animationFps, true);

	sprite.createAnimation("IdleDown", { 24 });
	sprite.createAnimation("MoveDown", { 25,26,27,28,29 }, animationFps, true);


}

float theta = 0;

void Enemy::update(float delta) {
	__super::update(delta);


	//movement.direction = Vector2D(cos(theta / 500), sin(theta / 500));
	//movement.velocity.x = speed * movement.direction.x;
	//movement.velocity.y = speed * movement.direction.y;

	theta++;

	walking = (movement.direction.x != 0 || movement.direction.y != 0); //walking only true when the x or y direction don't equal 0

	//get the current walkingDirection, used for animations
	if (movement.direction.x > 0 && movement.direction.y == 0) {
		walkDirection = WALKING_RIGHT;
	}
	else if (movement.direction.x > 0 && movement.direction.y < 0) {
		walkDirection = WALKING_UP_RIGHT;
	}
	else if (movement.direction.x == 0 && movement.direction.y < 0) {
		walkDirection = WALKING_UP;
	}
	else if (movement.direction.x < 0 && movement.direction.y < 0) {
		walkDirection = WALKING_UP_LEFT;
	}
	else if (movement.direction.x < 0 && movement.direction.y == 0) {
		walkDirection = WALKING_LEFT;
	}
	else if (movement.direction.x < 0 && movement.direction.y > 0) {
		walkDirection = WALKING_DOWN_LEFT;
	}
	else if (movement.direction.x == 0 && movement.direction.y > 0) {
		walkDirection = WALKING_DOWN;
	}
	else if (movement.direction.x > 0 && movement.direction.y > 0) {
		walkDirection = WALKING_DOWN_RIGHT;
	}
}

void Enemy::physicsUpdate(float delta) {
	__super::physicsUpdate(delta);

	if (movement.applyVelocity()) {
		//sprite.setSpeedScale(0.5);
	}
	else {
		//sprite.setSpeedScale(1);
	}

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