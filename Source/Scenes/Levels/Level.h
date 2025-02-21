#pragma once

#include "Source/UI/Button/Button.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/Pathfinding/NavigationMesh.h"
#include "Source/Entities/Player/Player.h"
#include "Source/Nodes/Camera/Camera.h"

class Level : public Node2D {
public:
	Level(std::string name);
	NavigationMesh navMesh;
	Player* currentPlayer;

	void ready() override;
	void update(float delta) override;
};
