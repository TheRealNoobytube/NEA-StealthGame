#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Entities/Player/Player.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"

class TestScene : public Node2D {
private:
	Player player;
	CollisionBody body;
	CollisionRect shape;

public:
	TestScene(std::string name = "Test Scene");

};