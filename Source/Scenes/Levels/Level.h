#pragma once

#include "Source/HUD/ItemsHUD.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/Pathfinding/NavigationMesh.h"
#include "Source/Nodes/Camera/Camera.h"

class Player;

class Level : public Node2D {
public:
	Level(std::string name);

	NavigationMesh* navMesh = new NavigationMesh();
	Player* currentPlayer;

	ItemsHUD* itemsHUD = new ItemsHUD();

	Node2D* itemLayer = new Node2D();
	Node2D* worldLayer = new Node2D();
	Node2D* projectileLayer = new Node2D();
	Node2D* playerLayer = new Node2D();
	Node2D* enemyLayer = new Node2D();
	Node* uiLayer = new Node();

	void ready() override;
	void update(float delta) override;
};

#include "Source/Entities/Player/Player.h"