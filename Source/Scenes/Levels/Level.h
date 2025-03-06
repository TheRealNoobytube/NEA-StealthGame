#pragma once

#include "Source/HUD/ItemsHUD.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/Pathfinding/NavigationMesh.h"
#include "Source/Nodes/Camera/Camera.h"
#include "Source/Weapons/Pistol/Pistol.h"


class Player;
class Enemy;

class Level : public Node2D {
private:

	
	struct Cell {

		Vector2D position;

		List<Cell*> neighbors;

		bool spawn = false;
		bool end = false;

	};


	const int tilesetWidth = 2;
	const int tilesetHeight= 2;

	int maxRooms = 5;

	List<Cell*> rooms;

	Vector2D roomsOffset = Vector2D(1000, 1000);

	Vector2D tileSize = Vector2D(10, 10);
	Vector2D roomDimensions = Vector2D(20, 20);

	Vector2D roomSize = Vector2D(tileSize.x * roomDimensions.x , tileSize.y * roomDimensions.y);

	bool exitCreated = false;

	void insertRoom(Cell* room);

	void createTile(int tileID, Vector2D position);


public:
	Level(std::string name);

	NavigationMesh* navMesh = new NavigationMesh();
	Player* currentPlayer = nullptr;

	ItemsHUD* itemsHUD = new ItemsHUD();

	Node2D* itemLayer = new Node2D();
	Node2D* worldLayer = new Node2D();
	Node2D* projectileLayer = new Node2D();
	Node2D* playerLayer = new Node2D();
	Node2D* enemyLayer = new Node2D();
	Node* uiLayer = new Node();

	

	void ready() override;
	void update(float delta) override;

	void generateLevel();
};

#include "Source/Entities/Player/Player.h"
#include "Source/Entities/Enemy/Enemy.h"