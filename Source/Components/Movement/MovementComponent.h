#pragma once
#include "Source/Nodes/Node.h"
#include "Source/Collision/Raycast/Raycast.h"

class Entity;
class CollisionBody;

class MovementComponent : public Node2D {
private:
	List<Vector2D> points;

	Raycast sweptRaycast;

	Vector2D findIntersectionSize(List<CollisionBody*> bodies);
	void findCollisions(Node* node, List<CollisionData>* data);

public:
	MovementComponent(Entity* entity = nullptr, std::string name = "MovementComponent");

	Vector2D velocity = Vector2D(0,0);
	//direction is a unit vector, meaning its magnitude will always be 1 or -1
	Vector2D direction = Vector2D(0,0);

	Entity* entity;

	void ready() override;
	void update(float delta) override;
	
	//returns true if any collisions took place, otherwise returns false
	bool applyVelocity();

};

#include "Source/Entities/Entity.h"