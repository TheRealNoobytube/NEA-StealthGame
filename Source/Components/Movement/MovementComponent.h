#pragma once
#include "Source/Nodes/Node.h"
#include "Source/Collision/CollisionBody.h"

class MovementComponent : public Node {
public:
	MovementComponent(std::string name = "MovementComponent");

	Vector2D velocity = Vector2D(0,0);
	//direction is a unit vector, meaning its magnitude will always be 1 or -1
	Vector2D direction = Vector2D(0,0);

	CollisionBody* entity;

	//returns true if any collisions took place, otherwise returns false
	bool applyVelocity();

};