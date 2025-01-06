#include "CollisionRect.h"

CollisionRect::CollisionRect(std::string name) : CollisionShape(name){

}

void CollisionRect::ready() {
	__super::ready();

}

void CollisionRect::update(float delta) {
	__super::update(delta);
	if (showCollisionShapes) {
		drawRect(getGlobalPosition(), size, Color(255, 0, 0));
	}
}

// body parameter should be the body youre checking collision against, not the parent body of this collision shape
CollisionBody* CollisionRect::detectCollisions(CollisionBody* body) {
	for (int i = 0; i < body->getChildCount(); i++) {

		//if the collision shape of the body is a rect, do rect_rect detection
		auto shape = dynamic_cast<CollisionRect*>(body->getChild(i)); 
		if (shape != nullptr) {
			if (rect_rectIsColliding(shape)) {
				return body;
			}
		}
	}

	return nullptr;
}

bool CollisionRect::rect_rectIsColliding(CollisionRect* shape) {
	bool xCollides = false;
	bool yCollides = false;

	Vector2D shapeGlobalPos = shape->getGlobalPosition();
	Vector2D globalPos = getGlobalPosition();

	if (globalPos.x <= shapeGlobalPos.x + shape->size.x && globalPos.x + size.x >= shapeGlobalPos.x) {
		xCollides = true;
	}
	if (globalPos.y <= shapeGlobalPos.y + shape->size.y && globalPos.y + size.y >= shapeGlobalPos.y) {
		yCollides = true;
	}

	return xCollides && yCollides;
}


void CollisionRect::setSize(Vector2D size) {
	if (size.x <= 0) {
		size.x = 1;
	}
	if (size.y <= 0) {
		size.y = 1;
	}
	this->size = size;
}

Vector2D CollisionRect::getSize() {
	return this->size;
}