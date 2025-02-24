#pragma once

#include "Source/HUD/ItemsHUD.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/Pathfinding/NavigationMesh.h"
#include "Source/Nodes/Camera/Camera.h"

class Player;

class Level : public Node2D {
public:
	Level(std::string name);
	NavigationMesh navMesh;
	Player* currentPlayer;

	ItemsHUD itemsHUD;

	Node2D itemLayer;
	Node2D worldLayer;
	Node2D playerLayer;
	Node2D enemyLayer;
	Node uiLayer;

	void ready() override;
	void update(float delta) override;
};

#include "Source/Entities/Player/Player.h"