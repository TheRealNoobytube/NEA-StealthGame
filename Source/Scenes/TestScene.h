#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Entities/Player/Player.h"

class TestScene : public Node2D {
private:
	Player player;

public:
	TestScene(std::string name = "Test Scene");

};