#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Collision/CollisionShapes/CollisionShape.h"

class CollisionBody : public Node2D {
public:
	CollisionBody(std::string name = "CollisionBody");

	void ready() override;
	void update(float delta) override;
	
	void compareBodies(Node* node, List<CollisionBody*>* bodies);
	List<CollisionBody*> requestCollisions();

};