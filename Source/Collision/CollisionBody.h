#pragma once
#include "Collision.h"
#include "Source/Collision/CollisionShapes/CollisionShape.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"

class CollisionBody : public Collision {
protected:
	List<CollisionShape*> shapes = List<CollisionShape*>();

public:

	CollisionBody(std::string name = "CollisionBody");

	int layer = 1;
	int mask = 1;

	void ready() override;
	void update(float delta) override;

	List<CollisionData> requestCollisions();

	void addCollisionShape(CollisionShape* shapes);
	List<CollisionShape*> getCollisionShapes();
};