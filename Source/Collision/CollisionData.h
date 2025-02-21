#pragma once
#include "Source/Application/Vector2D.h"

class CollisionBody;

struct CollisionData {

	bool colliding = false;
	Vector2D intersection = Vector2D(0, 0);
	Vector2D normal = Vector2D(0, 0);

	CollisionBody* body;


	CollisionData(bool colliding = false, Vector2D intersection = Vector2D(0, 0), CollisionBody* body = nullptr) {
		this->colliding = colliding;
		this->intersection = intersection;
		this->body = body;
	}
};

#include "CollisionBody.h"