#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Collision/CollisionShapes/CollisionShape.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"

class CollisionBody : public Node2D {
public:
	CollisionBody(std::string name = "CollisionBody");

	static enum CollisionLayer {
		WORLD = 1,
		ENTITIES = 2,
	};


	int layer = 1;
	int mask = 1;


	void ready() override;
	void update(float delta) override;
	
	void compareBodies(Node* node, List<CollisionBody*>* bodies);
	List<CollisionBody*> requestCollisions();

};