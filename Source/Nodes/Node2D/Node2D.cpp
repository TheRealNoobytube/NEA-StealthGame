#include "Node2D.h"


Vector2D Node2D::getGlobalPosition() {
	Vector2D globalPos = position;
	Node2D* parent = dynamic_cast<Node2D*>(getParent()); //Only Nodes that derive from Node2D have a position attribute

	if (parent != nullptr ) { //Make sure the parent derives from Node2D
		Vector2D ancestorPos = parent->getGlobalPosition(); //recursively call through all ancestor nodes to get global position
		globalPos.x += ancestorPos.x;
		globalPos.y += ancestorPos.y;
	}

	return globalPos;
}