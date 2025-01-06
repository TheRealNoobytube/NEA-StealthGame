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

	if (node != nullptr) {
		for (int i = 0; i < getChildCount(); i++) {
			auto shape = dynamic_cast<CollisionShape*>(getChild(i));
			if (shape != nullptr) {
				if (shape->getParent() != node) {
					CollisionBody* body = shape->detectCollisions(node);

					if (body != nullptr) {
						bodies->add(body);
					}
				}
			}
		}
	}

	for (int i = 0; i < currentNode->getChildCount(); i++) {
		compareBodies(currentNode->getChild(i), bodies);
	}
}


List<CollisionBody*> CollisionBody::requestCollisions() {
	List<CollisionBody*> bodies;
	compareBodies(getSceneTree()->getRoot(), &bodies);
	return bodies;
}