#pragma once
#include "../Collision.h"
#include "../CollisionBody.h"

class Raycast : public Collision {
private:
	CollisionBody* collider = nullptr;

	bool colliding = false;
	Vector2D intersectionPoint = Vector2D(0, 0);
	Vector2D contactNormal = Vector2D(0, 0);
	float contactTime = 0;

	bool checkForIntersections(Node* node);
	bool findRectIntersections(CollisionRect* rect);
	
	void resetValues();

public:
	Raycast(std::string name = "Raycast");

	Vector2D targetPosition = Vector2D(20, 3);

	bool visible = false;
	bool ignoreParent = true;
	int mask = 1;

	void ready() override;
	void update(float delta) override;

	void forceUpdateRaycast();

	void checkAgainstRect(CollisionRect* rect);

	bool isColliding();
	Vector2D getIntersectionPoint();
	Vector2D getContactNormal();
	float getContactTime();

	CollisionBody* getCollider();
};