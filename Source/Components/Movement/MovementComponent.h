#pragma once
#include "Source/Nodes/Node.h"

class Entity;

class MovementComponent : public Node {
public:
	MovementComponent(Entity* entity = nullptr, std::string name = "MovementComponent");

	Vector2D velocity = Vector2D(0,0);
	//direction is a unit vector, meaning its magnitude will always be 1 or -1
	Vector2D direction = Vector2D(0,0);

	Entity* entity;

	//returns true if any collisions took place, otherwise returns false
	bool applyVelocity();

};

#include "Source/Entities/Entity.h"