#include "Node2D.h"


Vector2D Node2D::getGlobalPosition() {
	Vector2D globalPos = position;
	Node2D* parent = dynamic_cast<Node2D*>(getParent()); //Only Nodes that derive from Node2D have a position attribute
	//if the parent doesn't derive from Node2D, the value of parent is null

	if (parent != nullptr ) { //Make sure the parent derives from Node2D
		Vector2D globalParentPos = parent->getGlobalPosition(); //recursively call through all parent nodes to get global position
		globalPos.x += globalParentPos.x;
		globalPos.y += globalParentPos.y;
	}

	return globalPos;
}