#pragma once
#include "Source/Nodes/Node2D/Node2D.h"

class CollisionBody;

class CollisionShape : public Node2D {
public:
	CollisionShape(std::string name = "CollisionShape");

	void ready() override;
	void update(float delta) override;

	virtual CollisionBody* detectCollisions(CollisionBody* body);
};

#include "Source/Collision/CollisionBody.h"