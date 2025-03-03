#pragma once
#include "Source/Nodes/Node2D/Node2D.h"


class Collision : public Node2D {
public:
	Collision(std::string name = "Collision") : Node2D(name){};

	enum CollisionLayer {
		WORLD = 1,
		ENTITIES = 2,
		ITEMS = 4,
		PROJECTILES = 8
	};
};