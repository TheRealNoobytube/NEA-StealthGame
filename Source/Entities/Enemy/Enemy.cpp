#include "Enemy.h"

Enemy::Enemy(std::string name) : Entity(name){
	addChild(sprite);
	addChild(collision);
	addChild(pathfinding);
	addChild(pathTimer);
}

void Enemy::ready() {
	__super::ready();

	auto level = dynamic_cast<Level*>(getSceneTree()->getCurrentScene());

	if (level != nullptr) {
		this->player = level->currentPlayer;
	}

	this->speed = 0.9;

	pathTimer->setLength(0.5);
	pathTimer->timeout.connect([this]() { this->onPathTimerTimeout(); });
	pathTimer->loop = true;
	pathTimer->start();

	collision->visible = true;
	collision->setSize(Vector2D(6, 11));
	collision->position = Vector2D(-collision->getSize().x / 2, -collision->getSize().y / 2);

	//mask = 1;
	
	sprite->position = Vector2D(-8, -16);
	sprite->visible = true;
	sprite->setTexture(getSceneTree()->getBasePath() + "../Assets/Enemies/Enemy.png");
	sprite->setHFrames(6);
	sprite->setVFrames(5);

	int animationFps = 10;

	sprite->createAnimation("IdleUp", { 0 });
	sprite->createAnimation("MoveUp", { 1,2,3,4,5 }, animationFps, false, false, true);

	sprite->createAnimation("IdleUpRight", { 6 });
	sprite->createAnimation("MoveUpRight", { 7,8,9,10,11 }, animationFps, false, false, true);

	sprite->createAnimation("IdleRight", { 12 });
	sprite->createAnimation("MoveRight", { 13,14,15,16,17 }, animationFps, false, false, true);

	sprite->createAnimation("IdleDownRight", { 18 });
	sprite->createAnimation("MoveDownRight", { 19,20,21,22,23 },animationFps, false, false, true);

	sprite->createAnimation("IdleDown", { 24 });
	sprite->createAnimation("MoveDown", { 25,26,27,28,29 }, animationFps, false, false, true);


}

void Enemy::update(float delta) {
	__super::update(delta);

	Vector2D direction = movement->direction.fixDirection();

	walking = (direction.x != 0 || direction.y != 0); //walking only true when the x or y direction don't equal 0

	//get the current walkingDirection, used for animations
	if (direction.x > 0 && direction.y == 0) {
		walkDirection = WALKING_RIGHT;
	}
	else if (direction.x > 0 && direction.y < 0) {
		walkDirection = WALKING_UP_RIGHT;
	}
	else if (direction.x == 0 && direction.y < 0) {
		walkDirection = WALKING_UP;
	}
	else if (direction.x < 0 && direction.y < 0) {
		walkDirection = WALKING_UP_LEFT;
	}
	else if (direction.x < 0 && direction.y == 0) {
		walkDirection = WALKING_LEFT;
	}
	else if (direction.x < 0 && direction.y > 0) {
		walkDirection = WALKING_DOWN_LEFT;
	}
	else if (direction.x == 0 && direction.y > 0) {
		walkDirection = WALKING_DOWN;
	}
	else if (direction.x > 0 && direction.y > 0) {
		walkDirection = WALKING_DOWN_RIGHT;
	}


}

void Enemy::physicsUpdate(float delta) {
	__super::physicsUpdate(delta);

	pathfinding->followPath(this);
	
	std::string state = "Idle";
	if (walking) {
		state = "Move";
	}

	switch (walkDirection) {
	case WALKING_RIGHT:
		sprite->flipH = false;
		sprite->play(state + "Right"); break;
	case WALKING_UP_RIGHT:
		sprite->flipH = false;
		sprite->play(state + "UpRight"); break;
	case WALKING_UP:
		sprite->play(state + "Up"); break;
	case WALKING_UP_LEFT:
		sprite->flipH = true;
		sprite->play(state + "UpRight"); break;
	case WALKING_LEFT:
		sprite->flipH = true;
		sprite->play(state + "Right"); break;
	case WALKING_DOWN_LEFT:
		sprite->flipH = true;
		sprite->play(state + "DownRight"); break;
	case WALKING_DOWN:
		sprite->play(state + "Down"); break;
	case WALKING_DOWN_RIGHT:
		sprite->flipH = false;
		sprite->play(state + "DownRight"); break;
	}
}


void Enemy::onPathTimerTimeout() {
	if (!disableAI) {
		pathfinding->findPath(position, player->position);
	}
}

void Enemy::onDeath(float damage) {
	queueFree();
}