#include "MovementComponent.h"

MovementComponent::MovementComponent(std::string name) : Node(name) {

}

bool MovementComponent::applyVelocity() {
	bool isColliding = false;

	//check if x position movement is valid
	entity->position.x += velocity.x;
	List<CollisionBody*> bodies = entity->requestCollisions();
	while (bodies.getSize() > 0) {
		bodies.clear();
		entity->position.x -= velocity.x;
		bodies = entity->requestCollisions();
		isColliding = true;
	}
	bodies.clear();

	//check if y position movement is valid
	entity->position.y += velocity.y;
	bodies = entity->requestCollisions();
	while (bodies.getSize() > 0) {
		bodies.clear();
		entity->position.y -= velocity.y;
		bodies = entity->requestCollisions();
		isColliding = true;
	}

	return isColliding;
}