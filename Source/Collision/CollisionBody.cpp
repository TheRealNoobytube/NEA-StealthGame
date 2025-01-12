#include "CollisionBody.h"


CollisionBody::CollisionBody(std::string name) : Node2D(name){

}

void CollisionBody::ready() {
	__super::ready();
}

void CollisionBody::update(float delta) {
	__super::update(delta);

	//compareBodies(getSceneTree()->getRoot());
}

void CollisionBody::compareBodies(Node* currentNode, List<CollisionBody*>* bodies) {
	auto node = dynamic_cast<CollisionBody*>(currentNode); 

	if (node != this && node != nullptr) {//make sure the current node isn't the this one and that the current node derives from CollisionBody

		//use bitmask operation to check if the current node is in the same collision layer as this body's collision mask
		//makes sure we don't waste time checking collision with something that isn't in the same layer
		if (node->layer & (mask)) {

			//CollisionBodys can have multiple CollisionShapes in order to allow for more complex shapes without needing to create more bodies
			//because of this we go through each child of a CollisionBody and detect collisions in all of its CollisionShapes
			for (int i = 0; i < getChildCount(); i++) {
				auto shape = dynamic_cast<CollisionShape*>(getChild(i));
				if (shape != nullptr) { //make sure the current node derives from CollisionShape
					//we don't want to compare collisions with the current node we're looking at, so we check the shapes parent
					CollisionBody* body = shape->detectCollisions(node);

					if (body != nullptr) {
						bodies->add(body);
					}
				}
			}

		}
	}

	//depth first search to check with all the nodes in the current tree
	for (int i = 0; i < currentNode->getChildCount(); i++) {
		compareBodies(currentNode->getChild(i), bodies);
	}
}


List<CollisionBody*> CollisionBody::requestCollisions() {
	List<CollisionBody*> bodies;
	compareBodies(getSceneTree()->getRoot(), &bodies);
	return bodies;
}