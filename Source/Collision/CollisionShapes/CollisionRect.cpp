#include "CollisionRect.h"

CollisionRect::CollisionRect(std::string name) : CollisionShape(name){

}

void CollisionRect::ready() {
	__super::ready();

}

void CollisionRect::update(float delta) {
	__super::update(delta);
	if (visible) {
		Vector2D globalPos = getGlobalPosition();
		drawRect(globalPos, getSize(), testColor);
	}
}

// body parameter should be the body youre checking collision against, not the parent body of this collision shape
CollisionData CollisionRect::detectCollisions(CollisionBody* body) {

	for (int i = 0; i < body->getChildCount(); i++) {

		//if the collision shape of the body is a rect, do rect_rect detection
		auto shape = dynamic_cast<CollisionRect*>(body->getChild(i));


		if (shape != nullptr && !shape->disabled) {
			CollisionData data = rect_rectIsColliding(shape);

			if (data.colliding) {
				data.body = body;
				return data;
			}
		}
	}
	

	return CollisionData();
}


bool CollisionRect::point_rectIsColliding(Vector2D point) {
	bool xCollides = false;
	bool yCollides = false;

	Vector2D globalPos = getGlobalPosition();

	if (point.x <= globalPos.x + size.x && point.x >= globalPos.x) {
		xCollides = true;
	}
	if (point.y <= globalPos.y + size.y && point.y >= globalPos.y) {
		yCollides = true;
	}

	return xCollides && yCollides;
}

CollisionData CollisionRect::rect_rectIsColliding(CollisionRect* shape) {
	Vector2D intersectionAmount = Vector2D(0, 0);

	Vector2D shapeGlobalPos = shape->getGlobalPosition();
	Vector2D globalPos = getGlobalPosition();

	bool collideX = false;
	bool collideY = false;

	if (globalPos.x <= shapeGlobalPos.x + shape->size.x && globalPos.x + size.x >= shapeGlobalPos.x) {
		intersectionAmount.x = std::min(globalPos.x + size.x, shapeGlobalPos.x + shape->size.x) - std::max(globalPos.x, shapeGlobalPos.x);
		collideX = true;
	}
	if (globalPos.y <= shapeGlobalPos.y + shape->size.y && globalPos.y + size.y >= shapeGlobalPos.y) {
		intersectionAmount.y = std::min(globalPos.y + size.y, shapeGlobalPos.y + shape->size.y) - std::max(globalPos.y, shapeGlobalPos.y);
		collideY = true;
	}


	return CollisionData(collideX && collideY, intersectionAmount, nullptr);

	//return xCollides && yCollides;
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