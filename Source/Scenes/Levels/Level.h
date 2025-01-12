#pragma once

#include "Source/Entities/Player/Player.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/UI/Button/Button.h"
#include "Source/Entities/Enemy/Enemy.h"
#include "Source/Pathfinding/NavigationMesh.h"

class Level : public Node2D {
public:
	Level(std::string name);
	NavigationMesh navMesh;

	void ready() override;
};