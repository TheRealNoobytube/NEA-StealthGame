#pragma once
#include "Collision.h"
#include "Source/Collision/CollisionShapes/CollisionShape.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"


class CollisionBody : public Collision {
public:

	CollisionBody(std::string name = "CollisionBody");

	int layer = 1;
	int mask = 1;

	void ready() override;
	void update(float delta) override;
	
	void compareBodies(Node* node, List<CollisionData>* bodies);
	List<CollisionData> requestCollisions();

};