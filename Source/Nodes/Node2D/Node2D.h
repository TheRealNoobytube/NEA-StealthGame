#pragma once
#include "Source/Nodes/Node.h"

class Node2D : public Node {
public:
	Node2D(std::string name = "Node2D") : Node(name) {};

	Vector2D position = Vector2D(0,0);
	Vector2D scale = Vector2D(1,1);

	Vector2D getGlobalPosition();
};